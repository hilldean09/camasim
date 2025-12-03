
#include "core/manager.hpp"
#include "core/recorder.hpp"
#include "core/particle_cloud.hpp"
#include "core/structs.hpp"
#include "core/pre_controls.hpp"

int main() {

  CSIM::Manager<float> manager;

  manager.initialiseParticleNumber( 1'000'00 );
  manager.initialiseWithSeed( 4 );

  manager.initialiseParticleCloud();
  manager.initialiseCentralBody( 1'000'000'000, 1'000'000 );

  manager.initialiseSimulation( 0.000001 );

  CSIM::Recorder<float> recorder;

  recorder.initialiseManager( &manager );
  recorder.initialiseOutputFile( "testOuts.txt" );
  recorder.initialiseLengthWithTime( 1'000'000 );
  recorder.initialiseSamplingWithFrames( 1'000'000'000 );

  recorder.recordInitial();


  return 0;
}
