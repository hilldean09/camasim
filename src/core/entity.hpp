
#ifndef CSIM_ENTITY_HPP
#define CSIM_ENTITY_HPP

#include "pre_controls.hpp"
#include "structs.hpp"

namespace CSIM {

  template <class PrecT>
  class Entity {
  public:
    // Constructors //
    Entity();
    Entity( Vector<PrecT> position, Vector<PrecT> velocity, PrecT mass );


    // Accessors //
    inline Vector<PrecT> getPosition() const { return m_position; }
    inline Vector<PrecT> getVeloctiy() const { return m_velocity; }
    inline PrecT getMass() const { return m_mass; }


    // Mutators //
    void setPosition( Vector<PrecT> position );
    void setPosition( Vector<PrecT>* positionPtr );
    void setVelocity( Vector<PrecT> velocity );
    void setVelocity( Vector<PrecT>* velocityPtr );
    inline void setMass( PrecT mass ) { m_mass = mass; }

    void applyForce( Vector<PrecT> force );
    void applyAcceleration( Vector<PrecT> acceleration );


    // Logger //
    void printLog( int verbosity = 0 ) const;


  private:
    // Attributes //
    Vector<PrecT> m_position;
    Vector<PrecT> m_velocity;

    Vector<PrecT> m_acceleration;
    Vector<PrecT> m_force

    PrecT m_mass;

    // Initialisers //
    void initDefaults();

  };

}

// Implementation file
#include "entity.tpp"

#endif
