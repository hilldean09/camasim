
#ifndef CSIM_PARTICLE_CLOUD_HPP
#define CSIM_PARTICLE_CLOUD_HPP

#include "struct.hpp"

#include <cstdlib>

namespace CSIM {

  template <class PrecT>
  class Particle_Cloud {
    public:
      // Constructors //
      Particle_Cloud();


      // Initialisers //
      void initialise( unsigned long long int p_number );


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


      // Initialisers //
      void initDefaults();

      void initPNumber( unsigned long long int p_number );
      void initStatuses();

      void initPositions();
      void initVelocities();

      void initAccelerations();
      void initForces();

      void initMasses();
      void initRadii();
      void initPartialRestitution();

  };

}

#endif
