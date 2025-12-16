
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

#include <algorithm>
#include <string>
#include <vector>

namespace CSIM {

  // Constructors //
  Visualiser::Visualiser() {
    initDefaults();
  }

  // Initialisers //
  void Visualiser::initialise( std::string collectionFile ) {
    m_reader->SetFileName( collectionFile.c_str() );
    m_reader->UpdateInformation();

    extractTimeSteps();

    // Configuring
    m_compositeFilter->SetInputConnection( m_reader->GetOutputPort() );
    m_compositeFilter->UpdateTimeStep( m_minTime );

    m_pointMapper->SetInputConnection( m_compositeFilter->GetOutputPort() );
    m_pointActor->SetInputConnection( m_pointMapper->GetOutputPort() );

    m_renderer->AddActor( m_pointActor );
    m_window->AddRenderer( m_renderer );
    m_interactor->SetRenderWindow( m_window );

    m_scene->SetModeSequence();
    m_scene->SetFrameRate( 60 );
    m_scene->SetStartTime( m_minTime );
    m_scene->SetEndTime( m_maxTime );
    m_scene->AddCue( m_cue );

    m_callback->setCompositeFiler( m_compositeFilter );
    m_callback->setRenderWindow( m_window );

    m_cue->SetStartTime( m_minTime );
    m_cue->SetEndTime( m_maxTime );
    m_cue->AddObserver( vtkCommand::AnimationCueTickEvent, m_callback );
  }

  void Visualiser::initDefaults() {

    m_reader = vtkSmartPointer<vtkXMLCollectionReader>::New();
    m_compositeFiler = vtkSmartPointer<vtkCompositeGeometryFilter>::New();
    m_pointMapper = vtkSmartPointer<vtkPointGaussianMapper>::New();
    m_pointActor = vtkSmartPointer<vtkActor>::New();

    m_readerInfo = nullptr;
    m_minTime = 0.0;
    m_maxTime = 0.0;

    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_window = vtkSmartPointer<vtkRenderWindow>::New();
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    m_scene = vtkSmartPointer<vtkAnimationScene>::New();
    m_cue = vtkSmartPointer<vtkAnimationCue>::New();
    m_callback = vtkSmartPointer<CueCallback>::New();

  }


  // Methods //
  void Visualiser::visualise() {
    m_window->Render();
    m_interactor->Initialise();
    
    m_scene->Play();

    m_interactor->Start();
  }

  void Visualiser::extractTimeSteps() {

    m_readerInfo = m_reader->GetOutputInformation( 0 ); // 0 indicating an output port
    
    unsigned long long int totalTimeSteps = m_readerInfo->Length( vtkStreamingDemandDrivenPipeline::TIME_STEPS() );
    
    std::vector<float> times( totalTimeSteps );
    m_readerInfo>Get( vtkStreamingDemandDrivenPipeline::TIME_STEPS(), times.data() );

    auto [ tmpMinTime, tmpMaxTime ] = std::minmax_element( times.begin(), times.end() );
    m_minTime = tmpMinTime;
    m_maxTime = tmpMaxTime;

  }
  
  void Visualiser::CueCallback::Execute( vtkObject* caller, unsigned long eventId, void* callData ) override {
    // Ensuring tick based response
    if( eventID != vtkCommand::AnimationCueTickEvent ) return;

    // Tbh I don't fully understand this but it seems common
    auto* cue = vtkAnimationCue::SafeDownCast( caller );

    const float time = cue->GetAnimationTime();

    m_filter->UpdateTimeStep( time );

    m_window->Render();
  }

}

#endif
