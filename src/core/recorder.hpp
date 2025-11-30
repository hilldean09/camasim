
#ifndef CSIM_RECORDER_HPP
#define CSIM_RECORDER_HPP

#include "manager.hpp"
#include "pre_controls.hpp"
#include "structs.hpp"

#include <fstream>
#include <string>

namespace CSIM {

  template <class PrecT>
  class Recorder { 
    public:
      // Constructor //
      Recorder();
      
      // Initialisers //
      void initialiseManager( Manager<PrecT>* manager );
      void initialiseOutputFile( const char* fileName );
      void initialiseLengthWithFrames( unsigned long long int totalFrames );
      void initialiseLengthWithTime( PrecT totalTime );
      
      void initialiseSamplingWithFrames( unsigned long long int framesPerSample );
      void initialiseSamplingWithTime( PrecT timePerSample );
      void initialiseSamplingWithSamples( unsigned long long int totalSamples );


      // Methods //
      void recordInitial();

    private:
      // Attributes //
      Manager<PrecT>* m_managerPtr;
      std::ofstream m_outputFile;

      unsigned long long int m_p_number;
      unsigned long long int m_totalFrames;
      PrecT m_step;
      PrecT* m_radii;

      unsigned long long int m_framesPerSample;


      // Initialisers //
      void initDefaults();
      void initTotalFrames( unsigned long long int totalFrames );
      void initSampling( unsigned long long int framesPerSample );


      // Methods //
      void writeOutputHeader();
      void writeFrameData();
  };

}

#include "recorder.tpp"

#endif
