
#ifndef CSIM_CENTRAL_BODY_TPP
#define CSIM_CENTRAL_BODY_TPP

#include "pre_controls.hpp"
#include "structs.hpp"

namespace CSIM {

  // Initialisers //
  template <class PrecT>
  void Central_Body<PrecT>::initialise( PrecT mass, PrecT radius, Vector<PrecT> position ) {

    initDefaults();

    initPosition( positon );
    initMass( mass );
    initRadius( radius );

  }

  template <class PrecT>
  void Central_Body<PrecT>::initPosition( Vector<PrecT> position ) {
    m_position = position;
  }

  template <class PrecT>
  void Central_Body<PrecT>::initMass( PrecT mass ) {
    m_mass = mass;
  }

  template <class PrecT>
  void Central_Body<PrecT>::initRadius( PrecT radius ) {
    m_radius = radius;
  }

}

#endif 
