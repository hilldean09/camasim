
#ifndef CSIM_MANAGER_HPP
#define CSIM_MANAGER_HPP

#include "pre_controls.hpp"
#include "structs.hpp"
#include "particle_cloud.hpp"

namespace CSIM {

  template <class PrecT>
  class Manager {
    public:
      // Constructors //
      Manager();


      // Initialisers //
      void initialiseParticleNumber( unsigned long long int p_number );

      void initialiseWithoutSeed();
      void initialiseWithSeed( unsigned int seed );

      void initialiseParticleCloud();


    private:
      // Attributes //
      std::default_random_engine m_randomEngine;
      Particle_Cloud<PrecT> m_particleCloud;

      unsigned long long int m_p_number;

      bool m_isPNumberInitialised;
      bool m_isRandomEngineInitialised;


      // Initialisers //
      void initDefaults();

      void initRandomEngine( unsigned int seed );

      void initParticleCloud();


  };


}

#include "manager.tpp"

#endif
