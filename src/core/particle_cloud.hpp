
#ifndef CSIM_PARTICLE_CLOUD_HPP
#define CSIM_PARTICLE_CLOUD_HPP

#include "structs.hpp"

#include <cstdlib>
#include <random>

namespace CSIM {

  template <class PrecT>
  class Particle_Cloud {
    public:
      // Constructors //
      Particle_Cloud();


      // Initialisers //
      void initialise( unsigned long long int p_number, std::default_random_engine* randomEnginePtr );


      // Mutators //
      void setDistribution( char distribution, PrecT mean, PrecT standardDeviaion );

      // Misc //
      ~Particle_Cloud();


    private:
      // Attributes //
      Vec_Arrs<PrecT> m_positions;
      Vec_Arrs<PrecT> m_velocities;

      Vec_Arrs<PrecT> m_accelerations;
      Vec_Arrs<PrecT> m_forces;
      
      PrecT* m_masses;
      PrecT* m_radii;
      PrecT* m_partial_restitution;

      unsigned long long int m_p_number;
      char* m_statuses;

      std::default_random_engine* m_randomEnginePtr;

      /* Note that std::normal_distribution defaults to
       * a mean of 0 and standard deviation of 1
       */
      std::normal_distribution<PrecT> m_radialPositionDistribution;
      std::normal_distribution<PrecT> m_radialVelocityDistribution;
      std::normal_distribution<PrecT> m_massDistribution;
      std::normal_distribution<PrecT> m_radiusDistribution;
      std::normal_distribution<PrecT> m_partialRestitutionDistribution;

      std::uniform_real_distribution<PrecT> m_anglesDistribution;

      // Initialisers //
      void initDefaults();

      void initPNumber( unsigned long long int p_number );
      void initStatuses();

      void initGenerator( std::default_random_engine* randomEnginePtr );
      void initAnglesDistribution();

      void initPositions();
      void initVelocities();

      void initAccelerations();
      void initForces();

      void initMasses();
      void initRadii();
      void initPartialRestitutions();

      void generateRandomPosition( unsigned long long int idx );
      void generateRandomVelocity( unsigned long long int idx );

      void generateRandomMass( unsigned long long int idx );
      void generateRandomRadius( unsigned long long int idx);
      void generateRandomPartialRestitution( unsigned long long int idx );

  };

}

#endif
