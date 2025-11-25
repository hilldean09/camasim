
#ifndef CSIM_PARTICLE_CLOUD_TPP
#define CSIM_PARTICLE_CLOUD_TPP

#include <cstdlib>
#include <cmath>
#include <random>
#include <numbers>

#include "structs.hpp"

namespace CSIM {
  
  // Initialisers //
  template <class PrecT>
  void Particle_Cloud<PrecT>::initialise( unsigned long long int p_number, std::default_random_engine* randomEnginePtr ) {

    initDefaults();

    initPNumber( p_number );
    initStatuses();

    initRandomEngine( randomEnginePtr );
    initAnglesDistribution();

    initPositions();
    initVelocities();
    initAccelerations();
    initForces();

    initMasses();
    initRadii();
    initPartialRestitutions();

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initDefaults() {
    m_p_number = 1;
    m_randomEnginePtr  = nullptr;
    m_statuses = nullptr;

    m_positions = { nullptr, nullptr, nullptr, nullptr };
    m_velocities = { nullptr, nullptr, nullptr, nullptr };
    m_accelerations = { nullptr, nullptr, nullptr, nullptr };
    m_forces = { nullptr, nullptr, nullptr, nullptr };

    m_masses = nullptr;
    m_radii = nullptr;
    m_partial_restitutions = nullptr;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPNumber( unsigned long long int p_number ) {
    m_p_number = p_number;
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
  void Particle_Cloud<PrecT>::initRandomEngine( std::default_random_engine* randomEnginePtr ) {
    m_randomEnginePtr = randomEnginePtr;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initAnglesDistribution() {
    m_anglesDistribution = std::uniform_real_distribution<PrecT>( -1.0 * std::numbers::pi_v<PrecT>, std::numbers::pi_v<PrecT> );
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPositions() {
    m_positions.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );
    
    m_positions.setPtrs( m_p_number );

    // Initialising random particle positions
    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomPosition( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initVelocities() {
    m_velocities.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );

    m_velocities.setPtrs( m_p_number );

    // Initialising ranndom particle velocities
    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomVelocity( idx );
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
      generateRandomMass( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initRadii() {
    m_radii = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomRadius( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPartialRestitutions() {
    m_partial_restitutions = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomPartialRestitution( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomPosition( unsigned long long int idx ) {
    // Creating polar representation
    PrecT newPolar = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newAzimuth = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newRadius = m_radialPositionDistribution( *m_randomEnginePtr );

    Radial_Vector<PrecT> newRadialVector = { newPolar, newAzimuth, newRadius };

    // Cartesian representation
    Vector<PrecT> newVector = newRadialVector.toCartesian();

    // Assigning new values
    m_positions.x[ idx ] = newVector.x;
    m_positions.y[ idx ] = newVector.y;
    m_positions.z[ idx ] =  newVector.z;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomVelocity( unsigned long long int idx ) {
    // Creating polar representation
    PrecT newPolar = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newAzimuth = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newRadius = m_radialVelocityDistribution( *m_randomEnginePtr );

    Radial_Vector<PrecT> newRadialVector = { newPolar, newAzimuth, newRadius };

    // Cartesian representation
    Vector<PrecT> newVector = newRadialVector.toCartesian();

    // Assigning new values
    m_velocities.x[ idx ] = newVector.x;
    m_velocities.y[ idx ] = newVector.y;
    m_velocities.z[ idx ] =  newVector.z;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomMass( unsigned long long int idx ) {
    // Ensuring non-negative, non-zero mass
    PrecT newMass = -1;
    while( newMass <= 0 ) {
      newMass = m_massDistribution( *m_randomEnginePtr );
    }

    m_masses[ idx ] = newMass;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomRadius( unsigned long long int idx ) {
    // Ensuring non-negative, non-zero radius 
    PrecT newRadius = -1;
    while( newRadius <= 0 ) {
      newRadius = m_radiusDistribution( *m_randomEnginePtr );
    }

    m_radii[ idx ] = newRadius;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomPartialRestitution( unsigned long long int idx ) {
    // Ensuring 0 - 0.5 range
    PrecT newPartialRestitution = -1;
    while( newPartialRestitution < 0 || newPartialRestitution > 0.5 ) {
      newPartialRestitution = m_partialRestitutionDistribution( *m_randomEnginePtr );
    }

    m_partial_restitutions[ idx ] = newPartialRestitution;
  }


  // Mutators //
  template <class PrecT>
  void Particle_Cloud<PrecT>::setDistribution( const char distribution, PrecT mean, PrecT standardDeviation ) {
    /* 'p' for postion, 'v' for velocity,
     * 'm' for mass. 'r' for radius, and
     * 'e' for partial restitution (elasticity).
     */
    switch( distribution ) {
      case 'p':
        m_radialPositionDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'v':
        m_radialVelocityDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'm':
        m_massDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'r':
        m_radiusDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'e':
        m_partialRestitutionDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;

    }

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
    std::free( m_partial_restitutions );

  }

}

#endif
