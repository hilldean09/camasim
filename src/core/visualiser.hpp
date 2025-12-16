
#ifndef CSIM_VISUALISER_HPP
#define CSIM_VISUALISER_HPP

#include "pre_controls.hpp"
#include "structs.hpp"

#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCommand.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkPointGaussianMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkXMLCollectionReader.h>

#include <string>

namespace CSIM {

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
      vtkSmartPointer<vtkCompositeDataGeometryFilter> m_compositeFiler;
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
      vtkSmartPointer<CueCallback> m_callback;

      // Initialisers //
      void initDefaults();

      
      // Methods //
      void extractTimeSteps();

      
      // Classes //
      class CueCallback : vtkCommand {
        public:
          static CueCallback* New() { return new CueCallback; } // VTK compatbility
          
          CueCallback() {
            m_filter = nullptr;
            m_window = nullptr;
          }

          void setCompositeFilter( vtkCompositeDataGeometryFilter* filter ) { m_filter = filter; }
          void setRenderWindow( vtkRenderWindow* window ) { m_window = window; }

          void Execute( vtkObject* caller, unsigned long eventId, void* callData ) override;


        private:
          vtkCompositeDataGeometryFilter* m_filter;
          vtkRenderWindow* m_window;
      };
  };
  
}

#include "visualiser.tpp"

#endif
