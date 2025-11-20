
#include "pre_controls.hpp"
#include "structs.hpp"

namespace CSIM {

  // Constructors //
  template <class PrecT>
  Entity<PrecT>::Entity<PrecT> () {
    initDefaults();
  }

  template <class PrecT>
  Entity<PrecT>::Entity( Vector<PrecT> position, Vector<PrecT> velocity, PrecT mass ) {
    initDefaults();

    setPosition( position );
    setVelocity( velocity );
    setMass( mass );
  }

  
  // Initialisers //
  template <class PrecT>
  void Entity<PrecT>::initDefaults() {

    m_position = { 0, 0, 0, };
    m_velocity = { 0, 0, 0, };

    m_acceleration = { 0, 0, 0, };
    m_force = { 0, 0, 0, };

    m_mass = 1;

  }

  template <class PrecT>
  void Entity<PrecT>::setPosition( Vector<PrecT> position ) {

  }

  template <class PrecT>
  void Entity<PrecT>::setPosition( Vector<PrecT>* positionPtr );

  template <class PrecT>
  void Entity<PrecT>::setVelocity( Vector<PrecT> velocity );

  template <class PrecT>
  void Entity<PrecT>::setVelocity( Vector<PrecT>* velocityPtr );

}
