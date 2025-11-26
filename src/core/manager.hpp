
#ifndef CSIM_MANAGER_HPP
#define CSIM_MANAGER_HPP

#include "pre_controls.hpp"
#include "structs.hpp"
#include "particle_cloud.hpp"
#include "central_body.hpp"

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

      void initialiseCentralBody( PrecT mass, PrecT radius, Vector<PrecT> position = { 0.0, 0.0, 0.0 } );

      void initialiseSimulation( PrecT step );

      // Accessors //
      Vec_Arrs<PrecT> getParticlePositions();
      Vector<PrecT> getCentralBodyPosition();


      // Methods //


    private:
      // Attributes //
      std::default_random_engine m_randomEngine;

      Particle_Cloud<PrecT> m_particleCloud;
      Central_Body<PrecT> m_centralBody;

      unsigned long long int m_p_number;

      PrecT m_step;

      bool m_isPNumberInitialised;
      bool m_isRandomEngineInitialised;
      bool m_isSimulationInitialised;


      // Initialisers //
      void initDefaults();

      void initRandomEngine( unsigned int seed );

  };


}

#include "manager.tpp"

#endif
