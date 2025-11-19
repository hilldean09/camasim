
#ifndef CSIM_STRUCTS_H
#define CSIM_STRUCTS_H

namespace {

  template <class PrecT>
  struct PosVec {
    PrecT x;
    PrecT y;
    PrecT z;
  };

  template <class PrecT>
  struct VelVec {
    PrecT x;
    PrecT y;
    PrecT z;
  };

}

#endif
