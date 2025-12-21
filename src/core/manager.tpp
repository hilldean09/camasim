
#ifndef CSIM_MANAGER_TPP
#define CSIM_MANAGER_TPP

#include "pre_controls.hpp"
#include "structs.hpp"
#include "particle_cloud.hpp"

#include <random>
#include <chrono>

namespace CSIM {

  // Constructors //
  template <class PrecT>
  Manager<PrecT>::Manager() {
    initDefaults();
  }

  // Initialisers //
  template <class PrecT>
  void Manager<PrecT>::initialiseParticleNumber( unsigned long long int p_number ) {
    m_p_number = p_number;

    m_isPNumberInitialised = true;
  }

  template <class PrecT>
  void Manager<PrecT>::initialiseWithoutSeed() {
    initRandomEngine( (unsigned int) std::chrono::high_resolution_clock::now() );
  }

  template <class PrecT>
  void Manager<PrecT>::initialiseWithSeed( unsigned int seed ) {
    initRandomEngine( seed );
  }

  template <class PrecT>
  void Manager<PrecT>::initialiseParticleDistribution( const char distribution, PrecT mean, PrecT standardDeviation ) {
    m_particleCloud.setDistribution( distribution, mean, standardDeviation );
  }

  template <class PrecT>
  void Manager<PrecT>::initialiseParticleCloud() {
    if( m_isPNumberInitialised && m_isRandomEngineInitialised ) {
      m_particleCloud.initialise( m_p_number, &m_randomEngine );
    }
  }

  template <class PrecT>
  void Manager<PrecT>::initialiseCentralBody( PrecT mass, PrecT radius, Vector<PrecT> position ) {

    m_centralBody.initialise( mass, radius, position );

  }

  template <class PrecT>
  void Manager<PrecT>::initialiseSimulation( PrecT step ) {
    m_step = step;
    #if( CSIM_CUDA == 1 )
    m_particleCloud.setCudaConstants( step );
    #endif

    m_isSimulationInitialised = true;
  }
  
  template <class PrecT>
  void Manager<PrecT>::initDefaults() {

    m_step = 0;

    m_isPNumberInitialised = false;
    m_isRandomEngineInitialised = false;
    m_isSimulationInitialised = false;

  }

  template <class PrecT>
  void Manager<PrecT>::initRandomEngine( unsigned int seed) {
    m_randomEngine = std::default_random_engine( seed );

    m_isRandomEngineInitialised = true;
  }


  // Accessors //
  template <class PrecT>
  Vec_Arrs<PrecT> Manager<PrecT>::getParticlePositions() {
    return m_particleCloud.m_positions;
  }

  template <class PrecT>
  Vector<PrecT> Manager<PrecT>::getCentralBodyPosition() {
    return m_centralBody.m_position;
  }

  
  // Methods //
  template <class PrecT>
  void Manager<PrecT>::doStep() {
    m_particleCloud.applyVelocity();

  }

}

#endif
