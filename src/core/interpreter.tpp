
#ifndef CSIM_INTERPRETER_TPP
#define CSIM_INTERPRETER_TPP

#include "pre_controls.hpp"

#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkXMLPPolyDataWriter.h>
#include <vtkSmartPointer.h>

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <string>

namespace CSIM {
  
  // Constructors //
  template <class PrecT>
  Interpreter<PrecT>::Interpreter() {
    initDefaults();
  }

  
  // Initialisers //
  template <class PrecT>
  void Interpreter<PrecT>::initialise( std::string inputFileName ) { 
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
    m_outputDirectory += "_";
    m_outputDirectory += std::format( "{:%Y%m%d_%H%M%S}", std::chrono::system_clock::now() );

    m_positionsBuffer = { nullptr, nullptr, nullptr, nullptr };
  }

  
  // Methods //
  template <class PrecT>
  void Interpreter<PrecT>::interpretToVtk() {
    configureWriters();

    readHeaderWithoutRadii();
    allocateBuffers();
    readRadii();
    
    for( unsigned long long int frameIdx = 0; frameIdx < m_totalFrames; frameIdx++ ) {
      writeFrame( frameIdx );
    }

    writePvd();
  }

  template <class PrecT>
  void Interpreter<PrecT>::configureWriters() {
    vtkMultiProcessController* mpiController = vtkMultiProcessController::GetGlobalController();
    
    // Using ternary operator to seperate between parallel and serial responses
    long long int rank = mpiController ? mpiController->GetLocalProcessId() : 0;
    long long int totalProcesses = mpiController ? mpiController->GetNumberOfProcesses() : 1;

    m_pPolyDataWriter->SetInputData( m_polyDataBuffer );
    m_pPolyDataWriter->SetDataModeToAppended();

    m_pPolyDataWriter->SetNumberOfPieces( totalProcesses );
    m_pPolyDataWriter->SetStartPiece( rank );
    m_pPolyDataWriter->SetEndPiece( rank );
  }

  template <class PrecT>
  void Interpreter<PrecT>::readHeaderWithoutRadii() {
    m_inputFile.read( reinterpret_cast<char*>( &m_p_number ), sizeof( unsigned long long int ) );
    m_inputFile.read( reinterpret_cast<char*>( &m_totalFrames ), sizeof( unsigned long long int ) );
    m_inputFile.read( reinterpret_cast<char*>( &m_step ), sizeof( PrecT ) );

    #if( CSIM_DEBUG == 1 )
    CSIM_M_DEBUG_LOG( "#CSIM# readHeaderWithoutRadii : \n"
                      << "\tm_p_number : " << std::to_string( m_p_number )
                      << ", m_totalFrames : " << std::to_string( m_totalFrames )
                      << ", m_step : " << std::to_string( m_step ) );
    #endif
  }

  template <class PrecT>
  void Interpreter<PrecT>::readRadii() {
    
    // Setting sizes
    PrecT* radiiPrecT = ( PrecT* ) std::malloc( ( m_p_number + 1 ) * sizeof( PrecT ) );
    m_radiiArray->SetNumberOfTuples( m_p_number + 1 );

    // Reading
    m_inputFile.read( reinterpret_cast<char*>( radiiPrecT ), ( m_p_number + 1 ) * sizeof( PrecT ) );
    
    // Converting types
    for( unsigned long long int idx = 0; idx < ( m_p_number + 1 ); idx++ ) {
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
    m_positionsBuffer.arenaPtr = ( PrecT* ) std::malloc( 3 * ( m_p_number + 1 ) * sizeof( PrecT ) );
    m_positionsBuffer.setPtrs( m_p_number + 1 );

    m_pointsBuffer->SetNumberOfPoints( m_p_number + 1 );
    m_polyDataBuffer->SetPoints( m_pointsBuffer );
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

    m_pPolyDataWriter->SetFileName( framePvtpPath.c_str() );

    m_pPolyDataWriter->Write();
  }
  
  template <class PrecT>
  void Interpreter<PrecT>::readFrameIntoPrecTBuffer() {
    m_inputFile.read( reinterpret_cast<char*>( m_positionsBuffer.arenaPtr ), 3 * ( m_p_number + 1 ) * sizeof( PrecT ) );
  }

  template <class PrecT>
  void Interpreter<PrecT>::convertPrecTBufferToPoints() {
    static float singlePositionBuffer[ 3 ];
    
    for( unsigned long long int idx = 0; idx < ( m_p_number + 1 ); idx++ ) {
      singlePositionBuffer[ 0 ] = ( float ) m_positionsBuffer.x[ idx ];
      singlePositionBuffer[ 1 ] = ( float ) m_positionsBuffer.y[ idx ];
      singlePositionBuffer[ 2 ] = ( float ) m_positionsBuffer.z[ idx ];
      
      m_pointsBuffer->SetPoint( idx, singlePositionBuffer );
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
    std::string frameNumber = std::to_string( frameIdx );
    int padding = CSIM_VTK_FRAME_NUMBER_PADDING - frameNumber.length();

    output += std::string( padding, '0' );
    output += frameNumber;

    return output;
  }

  template <class PrecT>
  void Interpreter<PrecT>::writePvd() {
    std::ofstream outputFile;

    std::filesystem::path outputFilePath = m_outputDirectory;
    outputFilePath /= "csim_simulation.pvd";

    outputFile.open( outputFilePath, std::ios::out );
    
    outputFile << "<?xml version=\"1.0\"?>" << std::endl;
    outputFile << "<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;
    outputFile << "\t<Collection>" << std::endl;
    outputFile << std::endl;
  
    for( unsigned long long int frameIdx = 0; frameIdx < m_totalFrames; frameIdx++ ) {
      outputFile << buildDataSet( frameIdx ) << std::endl;
    }

    outputFile << "\t</Collection>" << std::endl;
    outputFile << "</VTKFile>" << std::endl;
  }

  template <class PrecT>
  std::string Interpreter<PrecT>::buildDataSet( unsigned long long int frameIdx ) {

    std::string output;

    output += "\t\t<DataSet timestep=\"";
    output += std::to_string( ( float ) ( frameIdx * m_step ) );
    output += "\" group=\"\" part=\"0\"\n";
    output += "\t\t\tfile=\"";
    
    std::filesystem::path pvtpFilePath = m_outputDirectory;
    pvtpFilePath /= buildFrameName( frameIdx );
    pvtpFilePath /= buildFrameName( frameIdx );
    pvtpFilePath += ".pvtp";

    output += ( std::string ) pvtpFilePath;
    output += "\"/>\n";

    return output;
  }


  // Misc //
  template <class PrecT>\
  Interpreter<PrecT>::~Interpreter() {
    std::free( m_positionsBuffer.arenaPtr );
  }
}

#endif
