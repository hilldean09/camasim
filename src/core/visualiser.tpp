
#ifndef CSIM_INTERPRETER_TPP
#define CSIM_INTERPRETER_TPP

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

  // Constructors //
  template <class PrecT>
  Interpreter<PrecT>::Interpreter() {
    initDefaults();
  }

  // Initialisers //
  template <class PrecT>
  void Interpreter<PrecT>::initialise( std::string collectionFile ) {
    m_reader->SetFileName( collectionFile.c_str() );
    m_reader->UpdateInformation();

    extractTimeSteps();

    // Configuring
    m_compositeFilter->SetInputConnection( m_reader->GetOutputPort() );
    m_pointMapper->SetInputConnection( m_compositeFilter->GetOutputPort() );
    m_pointActor->SetInputConnection( m_pointMapper->GetOutputPort() );

    m_renderer->AddActor( m_pointActor );
    m_window->AddRenderer( m_renderer );
    m_interactor->SetRenderWindow( m_window );

    m_scene->SetModeSequence();
    m_scene->SetFrameRate( 60 );
  }

  template <class PrecT>
  void Interpreter<PrecT>::initDefaults() {

    m_reader = vtkSmartPointer<vtkXMLCollectionReader>::New();
    m_compositeFiler = vtkSmartPointer<vtkCompositeGeometryFilter>::New();
    m_pointMapper = vtkSmartPointer<vtkPointGaussianMapper>::New();
    m_pointActor = vtkSmartPointer<vtkActor>::New();

    vtkInformation* m_readerInfo = nullptr;

    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_window = vtkSmartPointer<vtkRenderWindow>::New();
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    m_scene = vtkSmartPointer<vtkAnimationScene>::New();
    m_cue = vtkSmartPointer<vtkAnimationCue>::New();

  }


}

#endif
