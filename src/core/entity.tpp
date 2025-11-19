
#include "pre_controls.hpp"
#include "structs.hpp"

namespace CSIM {

  // Constructors //
  template <class PrecT>
  Entity<PrecT> () {
    initDefaults();
  }

  template <class PrecT>
  Entity<PrecT>( Vector<PrecT> position, Vector<PrecT> velocity, PrecT mass ) {
    initDefaults();

    setPosition( position );
    setVelocity( velocity );
    setMass( mass );
  }





}
