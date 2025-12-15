
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

    // Initialising writer
    m_pPolyDataWriter = vtkSmartPointer<vtkXMLPPolyDataWriter>::New();

    // Initialising data buffers
    m_radiiArray = vtkSmartPointer<vtkFloatArray>::New();
    m_pointsBuffer = vtkSmartPointer<vtkPoints>::New();
    m_polyDataBuffer = vtkSmartPointer<vtkPolyData>::New();

    // Configuring poly data components
    m_radiiArray->SetName( "Radii" );
    m_radiiArray->SetNumberOfComponents( 1 );
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
    configureWriters();

    readHeaderWithoutRadii();
    allocateBuffers();
    readRadii();
    
    for( int frameIdx = 0; frameIdx < m_totalFrames; frameIdx++ ) {
      writeFrame();
    }

    writePvd();
  }

  template <class PrecT>
  void Interpreter<PrecT>::configureWriters() {
    vtkMultiProcessController* mpiController = vtkMultiProcessController::GetGlobalController();
    
    // Using ternary operator to seperate between parallel and serial responses
    long long int rank = mpiController ? mpiController->GetLocalProcessId() : 0;
    long long int totalProcesses = mpiController ? mpiController->GetNumberOfProcesses() : 1;

    m_pPolyDataWriter->SetInput( m_polyDataBuffer );
    m_pPolyDataWriter->SetDataModeToAppended();

    m_pPolyDataWriter->SetNumberOfPieces( totalProcesses );
    m_pPolyDataWriter->SetStartPiece( rank );
    m_pPolyDataWriter->SetEndPiece( rank );
  }

  template <class PrecT>
  void Interpreter<PrecT>::readHeaderWithoutRadii() {
    ifstream.read( reinterpret_cast<char*>( &m_p_number ), sizeof( unsigned long long int ) );
    ifstream.read( reinterpret_cast<char*>( &m_totalFrames ), sizeof( unsigned long long int ) );
    ifstream.read( reinterpret_cast<char*>( &m_step ), sizeof( PrecT ) );
  }

  template <class PrecT>
  void Interpreter<PrecT>::readRadii() {
    
    // Setting sizes
    PrecT* radiiPrecT = std::malloc( ( m_p_number + 1 ) * sizeof( PrecT ) );
    m_radiiArray->SetNumberOfTuples( m_p_number + 1 );

    // Reading
    m_inputFile.read( reinterpret_cast<char*>( radiiPrecT ), ( m_p_number + 1 ) * sizeof( PrecT ) );
    
    // Converting types
    for( int idx = 0; idx < ( m_p_number + 1 ); idx++ ) {
      m_radiiArray->SetValue( idx, ( float ) radiiPrecT[ idx ] );
    }

    // Adding radii to poly data
    m_polyDataBuffer->GetPointData()->AddArray( m_radiiArray );
    m_polyDataBuffer->GetPointData()->SetActiveScalars( "Radii" );

    // Clean up
    std::free( radiiPrecT );
  }

  template <class PrecT>
  void Interpreter<PrecT>::allocateBuffers() {
    m_positionsBuffer.arenaPtr = std::malloc( 3 * ( m_p_number + 1 ) * sizeof( PrecT ) );
    m_positionsBuffer.setPtrs( m_p_number + 1 );

    m_pointsBuffer->SetNumberOfPoints( m_p_number + 1 );
    m_polyDataBuffer->SetPoints( m_positionsBuffer );
  }

  template <class PrecT>
  void Interpreter<PrecT>::writeFrame( unsigned long long int frameIdx ) {
    readFrameIntoPrecTBuffer();
    convertPrecTBufferToPoints();
    updateVtkObjects();
  
    std::string frameName = buildFrameName( frameIdx );

    std::filesystem::path frameDirectory = m_outputDirectory;
    frameDirectory /= frameName;

    std::filesystem::create_directory( frameDirectory );

    std::filesystem::path framePvtpPath = frameDirectory;
    framePvtpPath /= frameName;
    framePvtpPath += ".pvtp";

    m_pPolyDataWriter.SetFileName( framePvtpPath );

    m_pPolyDataWriter.Write();
  }
  
  template <class PrecT>
  void Interpreter<PrecT>::readFrameIntoPrecTBuffer() {
    m_inputFile.read( reinterpret_cast<char*>( m_positionsBuffer.arenaPtr ), 3 * ( m_p_number + 1 ) * sizeof( PrecT ) );
  }

  template <class PrecT>
  void Interpreter<PrecT>::convertPrecTBufferToPoints() {
    
    for( int idx = 0; idx < ( m_p_number + 1 ); idx++ ) {
      m_pointsBuffer->SetPoint( idx, { ( float ) m_positionsBuffer.x[ idx ],
                                       ( float ) m_positionsBuffer.y[ idx ],
                                       ( float ) m_positionsBuffer.z[ idx ] } )
    }

  }

  template <class PrecT>
  void Interpreter<PrecT>::updateVtkObjects() {

    m_pointsBuffer->Modified();
    m_polyDataBuffer->Modified();

  }

  template <class PrecT>
  std::string Interpreter<PrecT>::buildFrameName( unsigned long long int frameIdx ) {
    std::string output = "frame_";

    // Determining '0' padding
    std::string frameNumber = ( std::string ) frameIdx;
    int padding = CSIM_VTK_FRAME_NUMBER_PADDING - frameNumber.length();

    output.add( std::string( padding, '0' ) );
    output.add( frameNumber );

    return output;
  }


  // Misc //
  template <class PrecT>\
  Interpreter<PrecT>::~Interpreter() {
    std::free( m_positionsBuffer.arenaPtr );
  }
}

#endif
