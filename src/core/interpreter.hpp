
#ifndef CSIM_INTERPRETER_HPP
#define CSIM_INTERPRETER_HPP

#include "pre_controls.hpp"
#include "structs.hpp"

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>

#include <fstream>
#include <filesystem>
#include <std::string>

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

      unsigned long long int m_p_number;
      unsigned long long int m_totalFrames;
      PrecT m_step;

      Vec_Arrs<PrecT> m_positionsBuffer;

      vtkSmartPointer<vtkPolyDataWriter> m_polyDataWriter;
      vtkSmartPointer<vtkPoints> m_pointsBuffer;
      vtkSmartPointer<vtkPolyData> m_polyDataBuffer;

      // Initialisers //
      void intiDefaults();


      // Methods //
      void readHeaderWithoutRadii();
      void writeRadiiBinary();
      void allocateBuffers();
      void writeFrame();
      void writePvd();

  };

}

#endif 
