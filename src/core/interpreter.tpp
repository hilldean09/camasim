
#ifndef CSIM_INTERPRETER_TPP
#define CSIM_INTERPRETER_TPP

#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <string>

namespace CSIM {
  
  // Constructors //
  template <class PrecT>
  Interpreter<PrecT>::Interpreter() {
    initDefaults();
  }

  
  // Initialisers //
  template <class PrecT>
  void initialise( std::string inputFileName ) { 
    std::filesystem::create_directory( m_outputDirectory );
    
    m_inputFile.open( inputFileName, std::ios::in | std::ios::binary );
  }

  template <class PrecT>
  void Interpreter<PrecT>::initDefaults() {
    m_p_number = 0;
    m_totalFrames = 0;
    m_step = 0;

    m_outputDirectory = std::filesystem::path( "csim_vtk_output" );

    m_positionsBuffer = { nullptr, nullptr, nullptr, nullptr };
  }

  
  // Methods //
  template <class PrecT>
  void Interpreter<PrecT>::interpretToVtk() {
    readHeaderWithoutRadii();
    writeRadiiBinary();
    allocateBuffers();
    
    for( int frameIdx = 0; frameIdx < m_totalFrames; frameIdx++ ) {
      writeFrame();
    }

    writePvd();
  }


  // Misc //
  template <class PrecT>\
  Interpreter<PrecT>::~Interpreter() {
    std::free( m_positionsBuffer.arenaPtr );
  }
}

#endif
