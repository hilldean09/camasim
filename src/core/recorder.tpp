
#ifndef CSIM_RECORDER_TPP
#define CSIM_RECORDER_TPP

#include "manager.hpp"

#include <fstream>
#include <filesystem>
#include <string>

namespace CSIM {

  // Constructors //
  template <class PrecT>
  Recorder<PrecT>::Recorder() {
    initDefaults();
  }

  // Initialisers //
  template <class PrecT>
  void Recorder<PrecT>::initialiseManager( Manager<PrecT>* manager ) {
    m_managerPtr = manager;

    m_p_number = manager->getParticleNumber();
    m_step = manager->getStep();
    m_centralBodyRadius = manager->getCentralBody()->getRadius();
    m_radii = manager->getRadiiPtr();

    m_centralBodyPosition = manager->getCentralBody()->getPosition();
    m_positions = manager->getPositions();
  }

  template <class PrecT>
  void Recorder<PrecT>::initialiseOutputFile( const char* fileName ) {
    m_outputFileName = std::string( fileName );

    m_outputFile = std::ofstream( m_outputFileName.append( ".bin" ).c_str(), std::ios::out | std::ios::binary );
  }

  template <class PrecT>
  void Recorder<PrecT>::initialiseLengthWithFrames( unsigned long long int totalFrames ) {
    initTotalFrames( totalFrames );
  }

  template <class PrecT>
  void Recorder<PrecT>::initialiseLengthWithTime( PrecT totalTime ) {
    unsigned long long int totalFrames = ( unsigned long long int ) totalTime / m_step;
    initTotalFrames( totalFrames );
  }

  template <class PrecT>
  void Recorder<PrecT>::initialiseSamplingWithFrames( unsigned long long int framesPerSample ) {
    initSampling( framesPerSample );
  }

  template <class PrecT>
  void Recorder<PrecT>::initialiseSamplingWithTime( PrecT timePerSample ) {
    unsigned long long int framesPerSample = ( unsigned long long int ) timePerSample / m_step;
    initSampling( framesPerSample );
  }
  
  template <class PrecT> 
  void Recorder<PrecT>::initDefaults() {
    m_p_number = 0;
    m_totalFrames = 0;
    m_step = 0;
    m_centralBodyRadius = 0;
    m_radii = nullptr;

    m_centralBodyPosition = { 0, 0, 0 };
    m_positions = { nullptr, nullptr, nullptr, nullptr };

    m_framesPerSample = 0;
  }

  template <class PrecT>
  void Recorder<PrecT>::initialiseSamplingWithSamples( unsigned long long int totalSamples ) {
    unsigned long long int framesPerSample = ( unsigned long long int ) m_totalFrames / totalSamples;
    initSampling( framesPerSample );
  }
  
  template <class PrecT>
  void Recorder<PrecT>::initTotalFrames( unsigned long long int totalFrames ) {
    m_totalFrames = totalFrames;
  }

  template <class PrecT>
  void Recorder<PrecT>::initSampling( unsigned long long int framesPerSample ) {
    m_framesPerSample = framesPerSample;
  }

  
  // Methods //
  template <class PrecT>
  void Recorder<PrecT>::recordInitial() {
    unsigned long long int tmpTotalFrames = m_totalFrames;
    m_totalFrames = 3;
    
    writeOutputHeader();
    writeFrameData();
    writeFrameData();
    writeFrameData();

    m_totalFrames = tmpTotalFrames;
  }

  template <class PrecT>
  void Recorder<PrecT>::startRecording() {
    writeOutputHeader();
    writeFrameData();

    for( unsigned long long int frameIdx = 0;
         frameIdx < m_totalFrames;
         frameIdx++ ) {
      #if( CSIM_VERBOSITY > 1 )
      std::cout << "\r" << CSIM_LOG_HEADER( "Recorder::startRecording" ) 
                << "Calculating frame " << std::to_string( frameIdx );
      #endif

      m_managerPtr->doStep();
      
      if( frameIdx % m_framesPerSample == 0 ) {
        #if( CSIM_VERBOSITY > 1 )
        std::cout << std::endl << CSIM_LOG_HEADER( "Recorder::startRecording" ) 
                  << "Recording frame " << std::to_string( frameIdx ) << std::endl;
        #endif
        writeFrameData();
      }

    }

    #if( CSIM_VERBOSITY > 1 )
    std::cout << std::endl;
    #endif 
  }

  template <class PrecT>
  inline void Recorder<PrecT>::write( void* ptr, size_t size ) {
    m_outputFile.write( reinterpret_cast<const char*>( ptr ), size );
  }

  template <class PrecT>
  void Recorder<PrecT>::writeOutputHeader() {
    write( &m_p_number, sizeof( m_p_number ) );

    unsigned long long int totalRecordedFrames = m_totalFrames / m_framesPerSample;
    PrecT recordedSteps = m_step * m_framesPerSample;

    write( &totalRecordedFrames, sizeof( unsigned long long int ) );
    write( &recordedSteps, sizeof( PrecT ) );

    write( &m_centralBodyRadius, sizeof( PrecT ) );
    write( m_radii, m_p_number * sizeof( PrecT) );
  }

  template <class PrecT>
  void Recorder<PrecT>::writeFrameData() {
    write( &( m_centralBodyPosition.x ), sizeof( PrecT ) );
    write( m_positions.x, m_p_number * sizeof( PrecT ) );
    
    write( &( m_centralBodyPosition.y ), sizeof( PrecT ) );
    write( m_positions.y, m_p_number * sizeof( PrecT ) );

    write( &( m_centralBodyPosition.z ), sizeof( PrecT ) );
    write( m_positions.z, m_p_number * sizeof( PrecT ) );
  }

}

#endif
