
#include <iostream>

#include "core/interpreter.hpp"
#include "core/manager.hpp"
#include "core/recorder.hpp"
#include "core/particle_cloud.hpp"
#include "core/structs.hpp"
#include "core/pre_controls.hpp"

int main() {

  CSIM::Manager<float> manager;

  std::cout << "Initialising particle cloud" << std::endl;

  manager.initialiseParticleNumber( 1'000 ); // Must be >= 204 for some reason
  manager.initialiseWithSeed( 4 );

  manager.initialiseParticleDistribution( 'p', 5'000'000, 5'000'000 );
  manager.initialiseParticleDistribution( 'r', 1'000, 10'000 );
  manager.initialiseParticleDistribution( 'v', 10'000'000, 10'000 );

  manager.initialiseParticleCloud();

  std::cout << "Particle cloud intialised" << std::endl;

  manager.initialiseCentralBody( 1'000'000, 1'000'000 );

  manager.initialiseSimulation( 0.0001 );

  std::cout << "Manager fully initialised" << std::endl;

  CSIM::Recorder<float> recorder;

  recorder.initialiseManager( &manager );
  recorder.initialiseOutputFile( "testOuts" );
  recorder.initialiseLengthWithTime( 10 );
  recorder.initialiseSamplingWithFrames( 1'000 );

  std::cout << "Recorder initialised" << std::endl;
  std::cout << "Beginning recording" << std::endl;

  recorder.startRecording();

  std::cout << "Recording complete" << std::endl;
  std::cout << "Interpreting" << std::endl;

  CSIM::Interpreter<float> interpreter;
  interpreter.initialise( "testOuts.bin" );
  interpreter.interpretToVtk();

  std::cout << "Interpretation complete" << std::endl;

  return 0;
}
