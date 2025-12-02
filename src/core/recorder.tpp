
#ifndef CSIM_RECORDER_TPP
#define CSIM_RECORDER_TPP

#include "manager.hpp"

#include <fstream>

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
    m_radii = manager->getRadiiPtr();

    m_centralBodyRadius = manager->getCentralBody()->getRadius();
    m_centralBodyPosition = manager->getCentralBody()->getPosition();
  }

  template <class PrecT>
  void Recorder<PrecT>::initialiseOutputFile( const char* fileName ) {
    m_outputFile = std::ofstream( fileName, std::ios::out | std::ios::binary );
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
    m_radii = nullptr;

    m_centralBodyPosition = { 0, 0, 0 };
    m_centralBodyRadius = 0;

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
    writeOutputHeader();
    writeFrameData();
  }

  template <class PrecT>
  void Recorder<PrecT>::writeOutputHeader() {
    
  }

}

#endif
