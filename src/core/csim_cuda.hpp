
#ifndef CSIM_CUDA_HPP
#define CSIM_CUDA_HPP

#include "structs.hpp"

namespace CSIM::CSIM_CUDA {

  // particle_cloud.cu //
  template <class PrecT>
  void cu_p_applyVelocity( PrecT step, unsigned long long int p_number,
                           Vec_Arrs<Prec> positions, Vec_Arrs<PrecT> velocities );
  
}

#endif
