
#ifndef CSIM_PARTICLE_CLOUD_HPP
#define CSIM_PARTICLE_CLOUD_HPP

#include "struct.hpp"

namespace CSIM {

  template <class PrecT>
  class Particle_Cloud {
    public:
      // Constructors //
      Particle_Cloud();

      // Misc //
      ~Particle_Cloud();

    private:
      // Attributes //
      Vec_Arrs<PrecT> positions;
      Vec_Arrs<PrecT> velocities;

      Vec_Arrs<PrecT> accelerations;
      Vec_Arrs<PrecT> forces;
      
      PrecT* masses;


      // Initialisers //
      void initDefaults();

      void initPositions();
      void initVelocities();

      void initMasses();

  };

}

#endif
