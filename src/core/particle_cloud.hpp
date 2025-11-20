
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
      Particle_Cloud( unsigned int seed );


      // Initialisers //
      void initialise( unsigned long long int p_number, unsigned int seed );


      // Misc //
      ~Particle_Cloud();

    private:
      // Attributes //
      Vec_Arrs<PrecT> m_positions;
      Vec_Arrs<PrecT> m_velocities;

      Vec_Arrs<PrecT> m_accelerations;
      Vec_Arrs<PrecT> m_forces;
      
      PrecT* m_masses;

      unsigned int m_seed;
      unsigned long long int m_p_number;


      // Initialisers //
      void initDefaults();

      void initSeed();

      void initPositions();
      void initVelocities();

      void initMasses();

  };

}

#endif
