
#include "csim_cuda.hpp"
#include "structs.hpp"

namespace CSIM::CSIM_CUDA {

  namespace Kernel {
    template<class PrecT> __constant__ PrecT ker_step;
    template<class PrecT> __constant__ PrecT ker_p_number;

    template <class PrecT>
    __global__ ker_p_applyVelocity( PrecT* __restrict__ positons, const PrecT* __restrict__ velocities ) {

    }

  }

  template <class PrecT>
  void cu_p_applyVelocity<PrecT>( PrecT step, unsigned long long int p_number,
                                  Vec_Arrs<PrecT> positions, Vec_Arrs<PrecT> velocities ) {
    // Symbol initialisation 
    cudaMemcpyToSymbol( Kernel::ker_step, step, sizeof( PrecT ) );
    cudaMemcpyToSymbol( Kernel::ker_p_number, p_number, sizeof( PrecT ) );

    // Device memory initialisation
    PrecT* d_positions; 
    cudaMalloc( &d_positions, p_number * sizeof( PrecT ) );
    cudaMemcpy( d_positions, positions, p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );

    PrecT* d_velocities;
    cudaMalloc( &d_velocities, p_number * sizeof( PrecT ) );
    cudaMemcpy( d_velocities, velocities, p_number * sizeof( PrecT ), cudaMemcpyHostToDevice );
    

    

    cudaFree( d_positions );
    cudaFree( d_velocities );
  }

}

