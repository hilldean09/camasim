
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

  // TODO: initialise buffers
  template <class PrecT>
  void cu_p_initialiseBuffers<PrecT>( Vec_Arrs<PrecT> positions, PrecT* d_positions,
                                      Vec_Arrs<PrecT> velocities, PrecT* d_velocities,
                                      Vec_Arrs<PrecT> accelerations, PrecT* d_accelerations,
                                      Vec_Arrs<PrecT> forces, PrecT* d_forces,
                                      unsigned long long int p_number ) {
    cudaMemcpy( d_positions, positions.arenaPtr, 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    cudaMemcpy( d_velocities, velocities.arenaPtr, 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    cudaMemcpy( d_accelerations, accelerations.arenaPtr, 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    cudaMemcpy( d_forces, forces.arenaPtr, 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );

  }


  template <class PrecT>
  void cu_p_freeBuffers<PrecT>( PrecT* d_positions,
                         PrecT* d_velocities,
                         PrecT* d_accelerations,
                         PrecT* d_forces ) {
    cudaFree( d_positions );
    cudaFree( d_velocities );
    cudaFree( d_accelerations );
    cudaFree( d_forces );
  }

  // TODO: implement allocate once structure


  template <class PrecT, bool preMemcpy, bool postMemcpy>
  void cu_p_applyVelocity<PrecT>( Vec_Arrs<PrecT> positions, PrecT* d_positions,
                                  Vec_Arrs<PrecT> velocities, PrecT* d_velocities,
                                  unsigned long long int p_number ) {
    if( preMemcpy ) {
      cudaMemcpy( d_positions, positions.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
      cudaMemcpy( d_velocities, velocities.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    }
    
    // Launch kernel
    Kernel::ker_p_applyTemporallyLinearChange<PrecT><<< CSIM_CUDA_BLOCKS, CSIM_CUDA_THREADS_PER_BLOCK >>>( d_positions, d_velocities );

    if( postMemcpy ) {
      cudaMemcpy( positions.arenaPtr, d_positions, 3 * p_number * sizeof( PrecT), cudaMemcpyDeviceToHost );
    }
  }

  template <class PrecT, bool preMemcpy, bool postMemcpy>
  void cu_p_applyAcceleration<PrecT>( Vec_Arrs<PrecT> velocities, PrecT* d_velocities,
                                      Vec_Arrs<PrecT> accelerations, PrecT* d_accelerations,
                                      unsigned long long int p_number ) {
    if( preMemcpy ) {
      cudaMemcpy( d_velocities, velocities.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
      cudaMemcpy( d_accelerations, accelerations.arenaPtr , 3 * p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    }
    
    // Launch kernel
    Kernel::ker_p_applyTemporallyLinearChange<PrecT><<< CSIM_CUDA_BLOCKS, CSIM_CUDA_THREADS_PER_BLOCK >>>( d_velocities, d_accelerations );

    if( postMemcpy ) {
      cudaMemcpy( velocities.arenaPtr, d_velocities, 3 * p_number * sizeof( PrecT), cudaMemcpyDeviceToHost );
    }
  }
  



#define CSIM_CUDA_INSTANTIATE( x ) \
            template void cu_p_setConstants< x >( x step, unsigned long long int p_number ); \
            template void cu_p_allocateBuffers< x >( x* d_positions, x* d_velocities, x* d_accelerations, x* d_forces, unsigned long long int p_number  ); \
            template void cu_p_initialiseBuffers< x >( Vec_Arrs< x > positions, x* d_positions, Vec_Arrs< x > velocities, x* d_velocities, Vec_Arrs< x x> accelerations, x* d_accelerations, Vec_Arrs< x x> forces, x* d_forces, unsigned long long int p_number ); \
            template void cu_p_freeBuffers< x >( x* d_positions, x* d_velocities, x* d_accelerations, x* d_forces ); \
            template void cu_p_applyVelocity< x, false, false >( Vec_Arrs< x > positions, x* d_positions, Vec_Arrs< x > velocities, x* d_velocities, unsigned long long int p_number ); \
            template void cu_p_applyVelocity< x, false, true >( Vec_Arrs< x > positions, x* d_positions, Vec_Arrs< x > velocities, x* d_velocities, unsigned long long int p_number ); \
            template void cu_p_applyVelocity< x, true, false >( Vec_Arrs< x > positions, x* d_positions, Vec_Arrs< x > velocities, x* d_velocities, unsigned long long int p_number ); \
            template void cu_p_applyVelocity< x, true, true >( Vec_Arrs< x > positions, x* d_positions, Vec_Arrs< x > velocities, x* d_velocities, unsigned long long int p_number ); \
            template void cu_p_applyAcceleration< x, false, false >( Vec_Arrs< x > velocities, x* d_velocities, Vec_Arrs< x > accelerations, x* d_accelerations, unsigned long long int p_number ); \
            template void cu_p_applyAcceleration< x, false, true >( Vec_Arrs< x > velocities, x* d_velocities, Vec_Arrs< x > accelerations, x* d_accelerations, unsigned long long int p_number ); \
            template void cu_p_applyAcceleration< x, true, false >( Vec_Arrs< x > velocities, x* d_velocities, Vec_Arrs< x > accelerations, x* d_accelerations, unsigned long long int p_number ); \
            template void cu_p_applyAcceleration< x, true, true >( Vec_Arrs< x > velocities, x* d_velocities, Vec_Arrs< x > accelerations, x* d_accelerations, unsigned long long int p_number ); 


  CSIM_CUDA_INSTANTIATE( float )


}

