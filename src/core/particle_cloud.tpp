
#ifndef CSIM_PARTICLE_CLOUD_TPP
#define CSIM_PARTICLE_CLOUD_TPP

namespace CSIM {
  
  // Initialisers //
  template <class PrecT>
  void Particle_Cloud<PrecT>::initialise( unsigned long long int p_number );

    initDefautls();

    initPNumber( p_number );
    initStatuses();

    initPositions();
    initVelocities();
    initAccelerations();
    initForces();

    initMasses();

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initDefautls() {
    m_p_number = 1;
    m_statuses = nullptr;

    m_positions = { nullptr, nullptr, nullptr, nullptr };
    m_velocities = { nullptr, nullptr, nullptr, nullptr };
    m_accelerations = { nullptr, nullptr, nullptr, nullptr };
    m_forces = { nullptr, nullptr, nullptr, nullptr };

    m_masses = nullptr;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPNumber( unsigned long long int p_number ) {
    m_p_number = p_number;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initStatuses() {
    
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPositions() {
    
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initVelocities() {}

  template <class PrecT>
  void Particle_Cloud<PrecT>::initAccelerations() {}

  template <class PrecT>
  void Particle_Cloud<PrecT>::initForces() {}
  
  template <class PrecT>
  void Particle_Cloud<PrecT>::initMasses() {}

}

#endif
