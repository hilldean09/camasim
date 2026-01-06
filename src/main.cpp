
#include <iostream>
#include <string>
#include <algorithm>

#include "core/interpreter.hpp"
#include "core/manager.hpp"
#include "core/recorder.hpp"
#include "core/particle_cloud.hpp"
#include "core/structs.hpp"
#include "core/pre_controls.hpp"

int main() {

  CSIM::Manager<float> manager;

  std::cout << "Initialising particle cloud" << std::endl;

  // The number of particles
  manager.initialiseParticleNumber( 20'000 ); // Must be >= 204 for some reason

  // The seed to be used, must be an integer
  manager.initialiseWithSeed( 4 );

  /* Distribution initialisation is in the format [type], [mean], 
   * [standard deviation]. The followig types are available:
   *  p[osition] : The particles' intiail radial distance.
   *  r[adius] : The radii of the particles themselves.
   *  v[elocity] : The magnitude of the particles' intiial
   *    velocity.
   *  m[ass] : The particles' mass.
   *  e[lasticity] : Actually represents the "half-restitution" to
   *    be used in calculating the elasticity of particle collisions.
   */
  manager.initialiseParticleDistribution( 'p', 5'000'000, 5'000'000 );
  manager.initialiseParticleDistribution( 'r', 1'000, 10'000 );
  manager.initialiseParticleDistribution( 'v', 10'000'000, 10'000 );
  manager.initialiseParticleDistribution( 'm', 1'000, 1'000 );
  manager.initialiseParticleDistribution( 'e', 0.25, 0.1 );

  manager.initialiseParticleCloud();

  std::cout << "Particle cloud intialised" << std::endl;

  // The mass and radius of the central body
  manager.initialiseCentralBody( 1'000'000, 1'000'000 );

  // The simulation step
  manager.initialiseSimulation( 0.0001 );

  std::cout << "Manager fully initialised" << std::endl;

  CSIM::Recorder<float> recorder;

  std::string binaryFileName = "csim_binary_output_";
  binaryFileName += std::format( "{:%Y%m%d_%H%M%S}", std::chrono::system_clock::now() );

  recorder.initialiseManager( &manager );
  recorder.initialiseOutputFile( binaryFileName.c_str() );

  // The simulation length measured in time
  recorder.initialiseLengthWithTime( 10 );

  /* The sampling rate features in frames, i.e. a frame is recorded 
   * every [X] frames.
   */
  recorder.initialiseSamplingWithFrames( 1'000 );

  std::cout << "Recorder initialised" << std::endl;
  std::cout << "Beginning recording" << std::endl;

  recorder.startRecording();

  std::cout << "Recording complete" << std::endl;
  std::cout << "Interpreting" << std::endl;

  CSIM::Interpreter<float> interpreter;

  binaryFileName += ".bin";

  interpreter.initialise( binaryFileName.c_str() );
  interpreter.interpretToVtk();

  std::cout << "Interpretation complete" << std::endl;

  return 0;
}
