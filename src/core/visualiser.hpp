
#ifndef CSIM_VISUALISER_HPP
#define CSIM_VISUALISER_HPP

#include "pre_controls"
#include "structs.hpp"

#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCommand.h>
#include <vtkCompositeGeometryFilter.h>
#include <vtkPointGaussianMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkXMLCollectionReader.h>

#include <string>

namespace CSIM {

  template <class PrecT>
  class Visualiser {
    public:
      // Constructors //
      Visualiser();
  

      // Initialisers //
      void initialise( std::string collectionFile );


      // Methods //
      void visualise();

    private:
      // Attributes //
      vtkSmartPointer<vtkXMLCollectionReader> m_reader;
      vtkSmartPointer<vtkCompositeGeometryFilter> m_compositeFiler;
      vtkSmartPointer<vtkPointGaussianMapper> m_pointMapper;
      vtkSmartPointer<vtkActor> m_pointActor;

      vtkInformation* m_readerInfo;
      float m_minTime;
      float m_maxTime;

      vtkSmartPointer<vtkRenderer> m_renderer;
      vtkSmartPointer<vtkRenderWindow> m_window;
      vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;

      vtkSmartPointer<vtkAnimationScene> m_scene;
      vtkSmartPointer<vtkAnimationCue> m_cue;

      // Initialisers //
      void initDefaults();

      
      // Methods //
      void extractTimeSteps();
  };
  
}

#include "visualiser.tpp"

#endif
