
#include "core/manager.hpp"
#include "core/particle_cloud.hpp"
#include "core/structs.hpp"
#include "core/pre_controls.hpp"

int main() {

  CSIM::Manager<float> manager;

  manager.initialiseParticleNumber( 1'000'00 );
  manager.initialiseWithSeed( 4 );
  manager.initialiseParticleCloud();

  manager.initialiseCentralBody( 1'000'000'000, 1'000'000 );

  return 0;
}
