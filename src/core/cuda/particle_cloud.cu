
#include "csim_cuda.hpp"
#include "../structs.hpp"
#include "../pre_controls.hpp"


namespace CSIM::CSIM_CUDA {

  namespace Kernel {

    template<class PrecT> __constant__ PrecT ker_step;
    __constant__ unsigned long long int ker_p_number;

    template <class PrecT>
    __global__ void ker_p_applyVelocity( PrecT* __restrict__ positions, const PrecT* __restrict__ velocities ) {
      const unsigned long long int stride = blockDim.x * gridDim.x;
  
      // Grid-stride loop
      for( unsigned long long int pid = threadIdx.x + blockIdx.x * blockDim.x;
           pid < ker_p_number;
           pid += stride ) {

        positions[ pid ] += velocities[ pid ] * ker_step<PrecT>;

      }

    }


  }
  
  template <class PrecT>
  void cu_p_setConstants<PrecT>( PrecT step, unsigned long long int p_number ) {
    // Symbol initialisation 
    cudaMemcpyToSymbol( Kernel::ker_step<PrecT>, &step, sizeof( PrecT ) );
    cudaMemcpyToSymbol( Kernel::ker_p_number, &p_number, sizeof( PrecT ) );
  }

  template <class PrecT>
  void cu_p_applyVelocity<PrecT>( Vec_Arrs<PrecT> positions, Vec_Arrs<PrecT> velocities, unsigned long long int p_number ) {
    // Device memory initialisation
    PrecT* d_positions; 
    cudaMalloc( &d_positions, p_number * sizeof( PrecT ) );
    cudaMemcpy( d_positions, positions.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );

    PrecT* d_velocities;
    cudaMalloc( &d_velocities, p_number * sizeof( PrecT ) );
    cudaMemcpy( d_velocities, velocities.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    
    // Launch kernel
    Kernel::ker_p_applyVelocity<PrecT><<< CSIM_CUDA_BLOCKS, CSIM_CUDA_THREADS_PER_BLOCK >>>( positions.arenaPtr, velocities.arenaPtr );

    // Clean up
    cudaFree( d_positions );
    cudaFree( d_velocities );
  }



#define CSIM_CUDA_INSTANTIATE( x ) \
            template void cu_p_setConstants< x >( x step, unsigned long long int p_number ); \
            template void cu_p_applyVelocity< x >( Vec_Arrs< x > positions, Vec_Arrs< x > velocities, unsigned long long int p_number );

  CSIM_CUDA_INSTANTIATE( float )


}

