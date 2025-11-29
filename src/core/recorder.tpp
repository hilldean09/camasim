
#ifndef CSIM_RECORDER_TPP
#define CSIM_RECORDER_TPP

#include "manager.hpp"

#include <fstream>

namespace CSIM {
  // Initialisers //
  template <class PrecT>
  void Recorder<PrecT>::initialiseManager( Manager<PrecT>* &manager ) {
    m_managerPtr = manager;
    m_step = manager->m_step;
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

}

#endif
