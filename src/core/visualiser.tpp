
#ifndef CSIM_VISUALISER_TPP
#define CSIM_VISUALISER_TPP

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

namspace CSIM{
  
  // Constructors //
  template <class PrecT>
  Visualiser<PrecT>::Visualiser() {
    initDefaults();
  }

  // Initialisers //
  template <class PrecT>
  void Visualiser<PrecT>::initDefaultss() {
    // Input file header
    m_p_number = 0;
    m_totalFrames = 0;
    m_step = 0;
    m_radii = nullptr;

    m_positionsBuffer = { nullptr, nullptr, nullptr, nullptr };

    // VTK objects (god help me)
    m_colors = vtkSmartPointer<vtkNamedColors>::New();
    m_p_points = vtkSmartPointer<vtkPoints>::New();
    m_p_radii = vtkSmartPointer<vtkDoubleArray>::New();
    m_p_polyData = vtkSmartPointer<vtkPolyData>::New();
    m_p_mapper = vtkSmartPointer<vtkPointGaussianMapper>::New();
    m_p_actor = vtkSmartPointer<vtkActor>::New();
    m_p_actorProperty = vtkSmartPointer<vtkProperty>::New();
    m_cb_sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    m_cb_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_cb_actor = vtkSmartPointer<vtkActor>::New();
    m_cb_actorProperty = vtkSmartPointer<vtkProperty>::New();
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  }

  template <class PrecT>
  void Visualiser<PrecT>::initInputFile( const char* inputFileName ) {
    m_inputFile = std::ifstream( inputFileName, std::ios::in | std::ios::binary );
  }
}

#endif 
