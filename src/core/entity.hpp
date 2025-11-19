
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
    Entity( PosVec<PrecT> position, VelVec<PrecT> velocity, PrecT mass );


    // Accessors //
    inline PosVec<PrecT> getPosition() const { return m_position; }
    inline VelVec<PrecT> getVeloctiy() const { return m_velocity; }
    inline PrecT getMass() const { return m_mass; }


    // Mutators //
    void setPosition( PrecT x, PrecT y, PrecT z );
    void setVelocity( PrecT x, PrecT y, PrecT z );
    inline void setMass( PrecT mass ) { m_mass = mass; }

    void applyForce( PrecT x, PrecT y, PrecT z );
    void applyAcceleration( PrecT x, PrecT y, PrecT z );


    // Logger //
    void printLog( int verbosity = 0 ) const;


  private:
    // Attributes //
    PosVec<PrecT> m_position;
    VelVec<PrecT> m_velocity;

    const PrecT m_mass;

  };

}

// Implementation file
#include "entity.tpp"

#endif
