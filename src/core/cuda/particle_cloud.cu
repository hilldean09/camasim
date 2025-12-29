
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
           pid ++ ) {

        positions[ pid ] += velocities[ pid ] * ker_step<PrecT>;

      }

    }


  }
  
  template <class PrecT>
  void cu_p_setConstants<PrecT>( PrecT step, unsigned long long int p_number ) {
    // Symbol initialisation 
    cudaMemcpyToSymbol( Kernel::ker_step<PrecT>, step, sizeof( PrecT ) );
    cudaMemcpyToSymbol( Kernel::ker_p_number, p_number, sizeof( PrecT ) );
  }

  template <class PrecT>
  void cu_p_applyVelocity<PrecT>( Vec_Arrs<PrecT> positions, Vec_Arrs<PrecT> velocities, unsigned long long int p_number ) {
    // Device memory initialisation
    PrecT* d_positions; 
    cudaMalloc( &d_positions, p_number * sizeof( PrecT ) );
    cudaMemcpy( d_positions, positions, p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );

    PrecT* d_velocities;
    cudaMalloc( &d_velocities, p_number * sizeof( PrecT ) );
    cudaMemcpy( d_velocities, velocities, p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    
    // Launch kernel
    unsigned long long int neededBlocks;
    neededBlocks = ( unsigned long long int ) 
                   ( p_number + CSIM_CUDA_THREADS_PER_BLOCK - 1 ) / CSIM_CUDA_THREADS_PER_BLOCK;

    ker_p_applyVelocity<PrecT><<< neededBlocks, CSIM_CUDA_THREADS_PER_BLOCK >>>( positions, velocities );

    // Clean up
    cudaFree( d_positions );
    cudaFree( d_velocities );
  }

#define CSIM_CUDA_INSTANTIATE( x ) \
            template x Kernel::ker_step< x >; \
            template __global__ void Kernel::ker_p_applyVelocity< x >( x* __restrict__ positons, const x* __restrict__ velocities ); \
            template void cu_p_setConstants< x >( x step, unsigned long long int p_number ); \
            template void cu_p_applyVelocity< x >( Vec_Arrs< x > positions, Vec_Arrs< x > velocities );

CSIM_CUDA_INSTANTIATE( float )
CSIM_CUDA_INSTANTIATE( double )


}

