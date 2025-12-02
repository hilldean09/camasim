
#ifndef CSIM_CENTRAL_BODY_HPP
#define CSIM_CENTRAL_BODY_HPP

#include "pre_controls.hpp"
#include "structs.hpp"

namespace CSIM {

  template <class PrecT>
  class Central_Body {
    public:
      // Constructors //


      // Initialisers //
      void initialise( PrecT mass, PrecT radius, Vector<PrecT> position = { 0.0, 0.0, 0.0 } );


      // Accessors //
      Vector<PrecT> getPosition() { return m_position; }
      PrecT getRadius() { return m_radius; }

    private:
      // Attributes //
      Vector<PrecT> m_position;
    
      PrecT m_mass;
      PrecT m_radius;

      // Initialisers //
      void initDefaults();

      void initPosition( Vector<PrecT> position );
      void initMass( PrecT mass );
      void initRadius( PrecT radius );

  };

}

#include "central_body.tpp"

#endif
