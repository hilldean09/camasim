
#ifndef CSIM_VISUALISER_HPP
#define CSIM_VISUALISER_HPP

#include "pre_controls.hpp"
#include "structs.hpp"

#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCommand.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkNamedColors.h>
#include <vtkPointGaussianMapper.h>
#include <vtkProperty.h>
#include <vtkPVDReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkXMLCollectionReader.h>

#include <string>

namespace CSIM {

  class CueCallback : public vtkCommand {
    public:
      static CueCallback* New() { return new CueCallback; } // VTK compatbility
      
      void setRenderWindow( vtkRenderWindow* window ) { m_window = window; }
      void setReader( vtkPVDReader* reader ) { m_reader = reader; }
      void setReaderInfo( vtkInformation* readerInfo ) { m_readerInfo = readerInfo; }

      void Execute( vtkObject* caller, unsigned long eventId, void* callData ) override;


    private:
      vtkRenderWindow* m_window = nullptr;
      vtkPVDReader* m_reader = nullptr;
      vtkInformation* m_readerInfo = nullptr;

  };

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
      vtkSmartPointer<vtkNamedColors> m_colors;
  
      vtkSmartPointer<vtkPVDReader> m_reader;
      vtkSmartPointer<vtkPointGaussianMapper> m_pointMapper;

      vtkSmartPointer<vtkActor> m_pointActor;
      vtkSmartPointer<vtkProperty> m_pointProperty;

      vtkInformation* m_readerInfo;
      float m_minTime;
      float m_maxTime;

      vtkSmartPointer<vtkRenderer> m_renderer;
      vtkSmartPointer<vtkRenderWindow> m_window;
      vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;

      vtkSmartPointer<vtkAnimationScene> m_scene;
      vtkSmartPointer<vtkAnimationCue> m_cue;
      vtkSmartPointer<CueCallback> m_callback;

      // Initialisers //
      void initDefaults();

      
      // Methods //
      void extractTimeSteps();

  };
  
}

#include "visualiser.tpp"

#endif
