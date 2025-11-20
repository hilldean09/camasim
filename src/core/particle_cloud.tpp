
#ifndef CSIM_PARTICLE_CLOUD_TPP
#define CSIM_PARTICLE_CLOUD_TPP

namespace CSIM {
  
  // Initialisers //
  template <class PrecT>
  void Particle_Cloud<PrecT>::initialise( unsigned long long int p_number );
    initDefautls();

    initPNumber( p_number );



  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initDefautls() {
    m_positions = { nullptr, nullptr, nullptr };
    m_velocities = { nullptr, nullptr, nullptr };
    m_accelerations = { nullptr, nullptr, nullptr };
    m_forces = { nullptr, nullptr, nullptr };

    m_masses = nullptr;

    m_p_number = 1;

}

#endif
