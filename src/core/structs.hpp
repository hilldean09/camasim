
#ifndef CSIM_STRUCTS_H
#define CSIM_STRUCTS_H

#include <cmath>

namespace CSIM {

  template <class PrecT>
  struct Vector {

    PrecT x;
    PrecT y;
    PrecT z;

    PrecT getAbs() { return std::hypot<PrecT>( x, y, z ); }

  };

  template <class PrecT>
  struct Radial_Vector {
    PrecT polar;
    PrecT azimuth;
    PrecT radius;

    Vector<PrecT> getCartesian() {
      Vector<PrecT> output = { 0.f, 0.f, 0.f };

      PrecT newX = std::cos( azimuth ) * radius;
      PrecT newY = std::sin( azimuth ) * radius;
      PrecT newZ = std::sin( polar ) * radius;

      output = { newX, newY, newZ };

      return output;
    }

  };

  template <class PrecT>
  struct Vec_Arrs {

    PrecT* arenaPtr;
    PrecT* x;
    PrecT* y;
    PrecT* z;

    void setPtrs( unsigned long long int p_number ) {

      x = arenaPtr;
      y = arenaPtr + p_number;
      z = arenaPtr + p_number + p_number;

    }

  };

}

#endif
