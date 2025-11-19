
#ifndef CSIM_STRUCTS_H
#define CSIM_STRUCTS_H

#include <cmath>

namespace {

  template <class PrecT>
  struct Vector{

    PrecT x;
    PrecT y;
    PrecT z;

    PrecT getAbs() { return std::hypot<PrecT>( x, y, z ); }

  };

}

#endif
