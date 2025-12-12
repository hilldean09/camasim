
#ifndef CSIM_VISUALISER_HPP
#define CSIM_VISUALISER_HPP

#include "pre_controls.hpp"
#include "structs.hpp"

#include <vtkActor.h>
#include <vtkDoubleArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointGaussianMapper.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include <fstream>
#include <string>

namespace CSIM {

  template <class PrecT>
  class Visualiser {
    public:
      // Constructors //
      Visualiser();

      void initialise( std::string inputFileName );

      void startInitial();

      
      // Misc //
      ~Visualiser();

    private:
      // Attributes //
      std::ifstream m_inputFile;

      unsigned long long int m_p_number;
      unsigned long long int m_totalFrames;
      PrecT m_step;
      PrecT* m_radii;

      Vec_Arrs<PrecT> m_positionsBuffer;

      // General VTK objects
      vtkSmartPointer<vtkNamedColors> m_colors;

      // Particle VTK objects
      vtkSmartPointer<vtkPoints> m_p_points;
      vtkSmartPointer<vtkDoubleArray> m_p_radii;
      vtkSmartPointer<vtkPolyData> m_p_polyData;
      vtkSmartPointer<vtkPointGaussianMapper> m_p_mapper;
      vtkSmartPointer<vtkActor> m_p_actor;
      vtkSmartPointer<vtkProperty> m_p_actorProperty;

      // Central body VTK objects
      vtkSmartPointer<vtkSphereSource> m_cb_sphereSource;
      vtkSmartPointer<vtkPolyDataMapper> m_cb_mapper;
      vtkSmartPointer<vtkActor> m_cb_actor;
      vtkSmartPointer<vtkProperty> m_cb_actorProperty;

      // Rendering VTK objects
      vtkSmartPointer<vtkRenderer> m_renderer;
      vtkSmartPointer<vtkRenderWindow> m_renderWindow;
      vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;

      
      // Initialisers //
      void initDefaults();
      void initInputFile( const char* inputFileName );
      void initInputHeader();


      // Methods //
      void loadFrame( unsigned long long int frameIdx );
      void updateRender();
  };

}

#include "visualiser.tpp"

#endif
