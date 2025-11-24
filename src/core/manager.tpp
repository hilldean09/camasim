
#ifndef CSIM_MANAGER_TPP
#define CSIM_MANAGER_TPP

#include "particle_cloud.hpp"
#include "structs.hpp"
#include "pre_controls.hpp"

#include <random>
#include <chrono>

namespace CSIM {

  // Constructors //
  template <PrecT>
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
    initRandomEngne( (unsigned int) std::chrono::high_resolution_clock::now() );
  }

  template <class PrecT>
  void Manager<PrecT>::initialiseWithSeed( unsigned int seed ) {
    initRandomEngne( seed );
  }

  template <class PrecT>
  void initRandomEngine( unsigned int seed) {
    m_randomEngine = ran
  }
  
  template <class PrecT>
  void Manager<PrecT>::initDefaults() {

    m_isPNumberInitialised = false;
    m_isRandomEngineInitialised; = false;

  }

  template <class PrecT>
  void initRandomEngine( unsigned int seed) {
    m_randomEngine = std::default_random_engine( seed );
  }

}

#endif
