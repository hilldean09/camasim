
#ifndef CSIM_PARTICLE_CLOUD_TPP
#define CSIM_PARTICLE_CLOUD_TPP

namespace CSIM {
  
  // Initialisers //
  template <class PrecT>
  void Particle_Cloud<PrecT>::initialise() {


  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initDefautls() {
    m_positions = { nullptr, nullptr, nullptr };
    m_velocities = { nullptr, nullptr, nullptr };
    m_accelerations = { nullptr, nullptr, nullptr };
    m_forces = { nullptr, nullptr, nullptr };

    m_masses = nullptr;

    m_seed = 0;
    m_p_number = 1;

}

#endif
