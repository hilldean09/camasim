
#include "core/visualiser.hpp"

#include <string>

int main( int argc, char** argv ) {

  CSIM::Visualiser visualiser;
  visualiser.initialise( std::string( argv[ 1 ] ) );

  visualiser.visualise();

}
