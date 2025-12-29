
#ifndef CSIM_CUDA_HPP
#define CSIM_CUDA_HPP

#include "../structs.hpp"

namespace CSIM::CSIM_CUDA {
  
  namespace Kernel {

  }
  
  template <class PrecT>
  void cu_p_setConstants( PrecT step, unsigned long long int p_number );

  // particle_cloud.cu //
  template <class PrecT>
  void cu_p_applyVelocity( Vec_Arrs<PrecT> positions, Vec_Arrs<PrecT> velocities );
  
}

#endif
