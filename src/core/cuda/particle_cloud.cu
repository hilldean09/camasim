
#include "csim_cuda.hpp"
#include "../structs.hpp"
#include "../pre_controls.hpp"


namespace CSIM::CSIM_CUDA {

  namespace Kernel {

    template<class PrecT> __constant__ PrecT ker_step;
    __constant__ unsigned long long int ker_p_number;

    /* 
     * Applies a change to the d_dest pointer that is
     * directly proportional to time, i.e. applying 
     * velocity or acceleration.
     */
    template <class PrecT>
    __global__ void ker_p_applyTemporallyLinearChange( PrecT* __restrict__ d_dest, const PrecT* __restrict__ d_src ) {
      const unsigned long long int stride = blockDim.x * gridDim.x;
  
      // Grid-stride loop
      for( unsigned long long int pid = threadIdx.x + blockIdx.x * blockDim.x;
           pid < 3 * ker_p_number;
           pid += stride ) {

        d_dest[ pid ] += d_src[ pid ] * ker_step<PrecT>;

      }

    }

  }
  
  template <class PrecT>
  void cu_p_setConstants<PrecT>( PrecT step, unsigned long long int p_number ) {
    // Symbol initialisation 
    cudaMemcpyToSymbol( Kernel::ker_step<PrecT>, &step, sizeof( PrecT ) );
    cudaMemcpyToSymbol( Kernel::ker_p_number, &p_number, sizeof( PrecT ) );
  }

  // TODO: Allocate once structure
  template <class PrecT>
  void cu_p_allocateBuffers<Prect>( PrecT* d_positions,
                             PrecT* d_velocities,
                             PrecT* d_accelerations,
                             PrecT* d_forces,
                             unsigned long long int p_number ) {
    
    cudaMalloc( &d_positions, 3 * p_number * sizeof( PrecT ) );
    cudaMalloc( &d_velocities, 3 * p_number * sizeof( PrecT ) );
    cudaMalloc( &d_accelerations, 3 * p_number * sizeof( PrecT ) );
    cudaMalloc( &d_forces, 3 * p_number * sizeof( PrecT ) );

  }

  template <class PrecT>
  void cu_p_applyVelocity<PrecT>( Vec_Arrs<PrecT> positions, Vec_Arrs<PrecT> velocities, unsigned long long int p_number ) {
    // Device memory initialisation
    PrecT* d_positions; 
    cudaMalloc( &d_positions, 3 * p_number * sizeof( PrecT ) );
    cudaMemcpy( d_positions, positions.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );

    PrecT* d_velocities;
    cudaMalloc( &d_velocities, 3 * p_number * sizeof( PrecT ) );
    cudaMemcpy( d_velocities, velocities.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    
    // Launch kernel
    Kernel::ker_p_applyTemporallyLinearChange<PrecT><<< CSIM_CUDA_BLOCKS, CSIM_CUDA_THREADS_PER_BLOCK >>>( d_positions, d_velocities );

    cudaMemcpy( positions.arenaPtr, d_positions, 3 * p_number * sizeof( PrecT), cudaMemcpyDeviceToHost );
    cudaMemcpy( velocities.arenaPtr, d_velocities, 3 * p_number * sizeof( PrecT), cudaMemcpyDeviceToHost );

    // Clean up
    cudaFree( d_positions );
    cudaFree( d_velocities );
  }

  template <class PrecT>
  void cu_p_applyAcceleration<PrecT>( Vec_Arrs<PrecT> velocities, Vec_Arrs<PrecT> accelerations, unsigned long long int p_number ) {
    // Device memory initialisation
    PrecT* d_velocities; 
    cudaMalloc( &d_velocities, 3 * p_number * sizeof( PrecT ) );
    cudaMemcpy( d_velocities, velocities.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );

    PrecT* d_accelerations;
    cudaMalloc( &d_accelerations, 3 * p_number * sizeof( PrecT ) );
    cudaMemcpy( d_accelerations, accelerations.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    
    // Launch kernel
    Kernel::ker_p_applyTemporallyLinearChange<PrecT><<< CSIM_CUDA_BLOCKS, CSIM_CUDA_THREADS_PER_BLOCK >>>( d_velocities, d_accelerations );

    cudaMemcpy( velocities.arenaPtr, d_velocities, 3 * p_number * sizeof( PrecT), cudaMemcpyDeviceToHost );
    cudaMemcpy( accelerations.arenaPtr, d_accelerations, 3 * p_number * sizeof( PrecT), cudaMemcpyDeviceToHost );

    // Clean up
    cudaFree( d_velocities );
    cudaFree( d_accelerations );
  }
  



#define CSIM_CUDA_INSTANTIATE( x ) \
            template void cu_p_setConstants< x >( x step, unsigned long long int p_number ); \
            template void cu_p_applyVelocity< x >( Vec_Arrs< x > positions, Vec_Arrs< x > velocities, unsigned long long int p_number ); \
            template void cu_p_applyAcceleration< x >( Vec_Arrs< x > velocities, Vec_Arrs< x > accelerations, unsigned long long int p_number );

  CSIM_CUDA_INSTANTIATE( float )


}

