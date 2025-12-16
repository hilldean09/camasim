
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
  void initialise( std::string collectionFile ) {
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


}

#endif
