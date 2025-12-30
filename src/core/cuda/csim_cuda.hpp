
#ifndef CSIM_CUDA_HPP
#define CSIM_CUDA_HPP

#include "../structs.hpp"

namespace CSIM::CSIM_CUDA {
  
  namespace Kernel {

  }
  
  template <class PrecT>
  void cu_p_setConstants( PrecT step, unsigned long long int p_number );
  
  template <class PrecT>
  void cu_p_allocateBuffers( PrecT* d_positions,
                             PrecT* d_velocities,
                             PrecT* d_accelerations,
                             PrecT* d_forces, 
                             unsigned long long int p_number );

  template <class PrecT>
  void cu_p_initialiseBuffers( Vec_Arrs<PrecT> positions, PrecT* d_positions,
                               Vec_Arrs<PrecT> velocities, PrecT* d_velocities,
                               Vec_Arrs<PrecT> accelerations, PrecT* d_accelerations,
                               Vec_Arrs<PrecT> forces, PrecT* d_forces,
                               unsigned long long int p_number );

  template <class PrecT>
  void cu_p_freeBuffers( PrecT* d_positions,
                         PrecT* d_velocities,
                         PrecT* d_accelerations,
                         PrecT* d_forces );

  // particle_cloud.cu //
  template <class PrecT, bool preMemcpy, bool postMemcpy>
  void cu_p_applyVelocity( Vec_Arrs<PrecT> positions, PrecT* d_positions,
                           Vec_Arrs<PrecT> velocities, PrecT* d_velocities,
                           unsigned long long int p_number );

  template <class PrecT, bool preMemcpy, bool postMemcpy>
  void cu_p_applyAcceleration( Vec_Arrs<PrecT> velocities, PrecT* d_velocities,
                               Vec_Arrs<PrecT> accelerations, PrecT* d_accelerations,
                               unsigned long long int p_number );
  
}

#endif
