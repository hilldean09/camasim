
#ifndef CSIM_RECORDER_HPP
#define CSIM_RECORDER_HPP

#include <fstream>

namespace CSIM {

  template <class PrecT>
  class Recorder { 
    public:
      
      // Initialisers //
      void initialiseManager( Manager<PrecT> &manager );
      void initialiseOutputFile( const char* fileName );
      void initialiseLengthWithFrames( unsigned long long int totalFrames );
      void initialiseLengthWithTime( PrecT totalTime );

    private:
      // Attributes //
      Manager<PrecT>* m_managerPtr;
      std::basic_ofstream m_outputFile;
      
      unsigned long long int m_totalFrames;

      // Initialisers //
      void initDefaults();
      void initTotalFrames( unsigned long long int totalFrames );


  };

}

#endif
