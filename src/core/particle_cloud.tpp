
#ifndef CSIM_PARTICLE_CLOUD_TPP
#define CSIM_PARTICLE_CLOUD_TPP

#include <cstdlib>
#include <random>

namespace CSIM {
  
  // Initialisers //
  template <class PrecT>
  void Particle_Cloud<PrecT>::initialise( unsigned long long int p_number, std::default_random_engine* randomEnginePtr );

    initDefautls();

    initPNumber( p_number );
    initRandomEngine( randomEnginePtr );
    initStatuses();

    initPositions();
    initVelocities();
    initAccelerations();
    initForces();

    initMasses();
    initRadii();
    initPartialRestitutions();

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initDefautls() {
    m_p_number = 1;
    m_randomEningePtr = nullptr;
    m_statuses = nullptr;

    m_positions = { nullptr, nullptr, nullptr, nullptr };
    m_velocities = { nullptr, nullptr, nullptr, nullptr };
    m_accelerations = { nullptr, nullptr, nullptr, nullptr };
    m_forces = { nullptr, nullptr, nullptr, nullptr };

    m_masses = nullptr;
    m_radii = nullptr;
    m_partial_restitution = nullptr;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPNumber( unsigned long long int p_number ) {
    m_p_number = p_number;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initRandomEngine( std::default_random_engine* randomEnginePtr ) {
    m_randomEningePtr = randomEnginePtr;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initStatuses() {
    m_statuses = (char*) std::malloc( m_p_number * sizeof( char ) );

    // Initialising all particles to active
    for( int idx = 0; idx < m_p_number; idx++ ) {
      m_statuses[ idx ] = (char) 1;
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPositions() {
    m_positios.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );
    
    m_positions.setPtrs( m_p_number );

    // Initialising random particle positions
    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomPosition( m_positions.arenaPtr, idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initVelocities() {
    m_velocities.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );

    m_velocities.setPtrs( m_p_number );

    // Initialising ranndom particle velocities
    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomVelocity( m_velocities.arenaPtr, idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initAccelerations() {
    m_accelerations.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );

    m_accelerations.setPtrs( m_p_number );

    for( int idx = 0; idx < 3 * m_p_number; idx++ ) {
      m_accelerations.arenaPtr[ idx ] = 0;
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initForces() {
    m_forces.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );

    m_forces.setPtrs( m_p_number );

    for( int idx = 0; idx < 3 * m_p_number; idx++ ) {
      m_forces.arenaPtr[ idx ] = 0;
    }
  }
  
  template <class PrecT>
  void Particle_Cloud<PrecT>::initMasses() {
    m_masses = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomMass( m_masses );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initRadii() {
    m_radii = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomRadius( m_radii );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPartialRestitutions() {
    m_partial_restitution = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomPartialRestitution( m_partial_restitutions );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomPosition( PrecT* arenaPtr, unsigned long long int p_number ) {

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomVelocity( PrecT* arenaPtr, unsigned long long int p_number ) {

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomMass( PrecT* arenaPtr, unsigned long long int p_number ) {

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomRadius( PrecTPosition* arenaPtr, unsigned long long int p_number ) {

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomPartialRestitution( PrecT* arenaPtr, unsigned long long int p_number ) {

  }


  // Misc //
  template <class PrecT>
  Particle_Cloud<PrecT>::~Particle_Cloud() {

    std::free( m_statuses );

    std::free( m_positions.arenaPtr );
    std::free( m_velocities.arenaPtr );
    std::free( m_accelerations.arenaPtr );
    std::free( m_forces.arenaPtr );

    std::free( m_masses );
    std::free( m_radii );
    std::free( m_partial_restitution );

  }

}

#endif
