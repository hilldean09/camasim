
#ifndef CSIM_INTERPRETER_HPP
#define CSIM_INTERPRETER_HPP

#include "pre_controls.hpp"
#include "structs.hpp"

#include <vtkFloatArray.h>
#include <vtkMultiProcessController.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkXMLPPolyDataWriter.h>
#include <vtkSmartPointer.h>

#include <fstream>
#include <filesystem>
#include <string>

namespace CSIM {

  template <class PrecT>
  class Interpreter {
    public:
      // Constructos //
      Interpreter();


      // Initialisers //
      void initialise( std::string inputFileName );


      // Methods //
      void interpretToVtk();


      // Misc //
      ~Interpreter();


    private:
      // Attributes //
      std::ifstream m_inputFile;
      std::filesystem::path m_outputDirectory;
      
      vtkSmartPointer<vtkXMLPPolyDataWriter> m_pPolyDataWriter;

      unsigned long long int m_p_number;
      unsigned long long int m_totalFrames;
      PrecT m_step;

      vtkSmartPointer<vtkFloatArray> m_radiiArray;

      unsigned long long int m_totalPiecesPerFrame;

      Vec_Arrs<PrecT> m_positionsBuffer;

      vtkSmartPointer<vtkPoints> m_pointsBuffer;
      vtkSmartPointer<vtkPolyData> m_polyDataBuffer;

      // Initialisers //
      void initDefaults();


      // Methods //
      void readHeaderWithoutRadii();
      void configureWriters();
      void readRadii();
      void allocateBuffers();
      void writeFrame( unsigned long long int frameIdx );

      void readFrameIntoPrecTBuffer();
      void convertPrecTBufferToPoints();
      void updateVtkObjects();
      std::string buildFrameName( unsigned long long int frameIdx );

      void writePvd();
      std::string buildDataSet( unsigned long long int );

  };

}

#include "interpreter.tpp"

#endif 
