
#include "manager.hpp"
#include "particle_cloud.hpp"
#include "structs.hpp"
#include "pre_controls.hpp"

int main() {

  CSIM::Manager<float> manager;

  manager.initialiseParticleNumber( 1'000'00 );
  manager.initialiseWithSeed( 4 );
  manager.initialiseParticleCloud();

  manager.initialiseCentralBody( 1'000'000'000, 1'000'000 );

  return 0;
}
