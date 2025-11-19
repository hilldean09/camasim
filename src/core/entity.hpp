
#ifndef CSIM_ENTITY_HPP
#define CSIM_ENTITY_HPP

#include "pre_controls.hpp"
#include "structs.hpp"
#include <string>

namespace CSIM {

  template <class PrecT>
  class Entity {
  public:
  
  private:
    // Attributes //
    PosVec m_position;
    VelVec m_velocity;
    PrecT m_mass;

  };

}

#endif
