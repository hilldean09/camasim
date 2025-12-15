
#ifndef CSIM_INTERPRETER_TPP
#define CSIM_INTERPRETER_TPP

#include "pre_controls.hpp"

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

    m_polyDataWriter = vtkSmartPointer<vtkPolyDataWriter>::New();
  }

  template <class PrecT>
  void Interpreter<PrecT>::initDefaults() {
    m_p_number = 0;
    m_totalFrames = 0;
    m_step = 0;

    m_outputDirectory = std::filesystem::path( CSIM_VTK_OUTPUT_DIRECTORY_NAME );

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

  template <class PrecT>
  void Interpreter<PrecT>::readHeaderWithoutRadii() {
    ifstream.read( reinterpret_cast<char*>( &m_p_number ), sizeof( unsigned long long int ) );
    ifstream.read( reinterpret_cast<char*>( &m_totalFrames ), sizeof( unsigned long long int ) );
    ifstream.read( reinterpret_cast<char*>( &m_step ), sizeof( PrecT ) );
  }

  template <class PrecT>
  void Interpreter<PrecT>::writeRadiiBinary() {
    std::ofstream radiiOutputFile;

    std::filesystem::path radiiOutputPath = m_outputDirectory;
    radiiOutputPath /= CSIM_VTK_RADII_BINARY_NAME;

    radiiOutputFile.open( radiiOutputPath, std::ios::out | std::ios::binary );
    
    PrecT* radiiPrecT = std::malloc( ( m_p_number + 1 ) * sizeof( PrecT ) );
    float* radiiFloat = std::malloc( ( m_p_number + 1 ) * sizeof( float ) );

    m_inputFile.read( reinterpret_cast<char*>( radiiPrecT ), ( m_p_number + 1 ) * sizeof( PrecT ) );
    
    // Converting types
    for( int idx = 0; idx < ( m_p_number + 1 ); idx++ ) {
      radiiFloat[ idx ] = ( float ) radiiPrecT[ idx ];
    }

    radiiOutputFile.write( reinterpret_cast<const char*>( radiiFlaot ), ( m_p_number + 1 ) * sizeof( float ) );
    
    // Clean up
    radiiOutputFile.close();

    std::free( radiiPrecT );
    std::free( radiiFloat );
  }

  template <class PrecT>
  void Interpreter<PrecT>::allocateBuffers() {
    m_positionsBuffer = std::malloc( 3 * ( m_p_number + 1 ) * sizeof( PrecT ) );

    m_pointsBuffer = vtkSmartPointer<vtkPoints>::New();
    m_polyDataBuffer = vtkSmartPointer<vtkPolyData>::New();
  }

  template <class PrecT>
  void Interpreter<PrecT>::writeFrame() {

  }


  // Misc //
  template <class PrecT>\
  Interpreter<PrecT>::~Interpreter() {
    std::free( m_positionsBuffer.arenaPtr );
  }
}

#endif
