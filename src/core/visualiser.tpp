
#ifndef CSIM_INTERPRETER_TPP
#define CSIM_INTERPRETER_TPP

#include "pre_controls.hpp"
#include "structs.hpp"

#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCommand.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkInformation.h>
#include <vtkPointGaussianMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkStreamingDemandDrivenPipeline.h>
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
    m_pointMapper->SetScaleArray( "Radii" );
    m_pointMapper->SetScaleArrayComponenet( 0 );
    m_pointMapper->SetScaleFactor( CSIM_POINT_SCALE_FACTOR );

    m_pointActor->SetMapper( m_pointMapper );

    m_renderer->AddActor( m_pointActor );

    m_window->AddRenderer( m_renderer );
    m_window->SetSize( 800, 600 );

    m_interactor->SetRenderWindow( m_window );

    m_scene->SetModeToSequence();
    m_scene->SetFrameRate( 60 );
    m_scene->SetStartTime( m_minTime );
    m_scene->SetEndTime( m_maxTime );
    m_scene->AddCue( m_cue );

    m_callback->setCompositeFilter( m_compositeFilter );
    m_callback->setRenderWindow( m_window );

    m_cue->SetStartTime( m_minTime );
    m_cue->SetEndTime( m_maxTime );
    m_cue->AddObserver( vtkCommand::AnimationCueTickEvent, m_callback );
  }

  void Visualiser::initDefaults() {

    m_reader = vtkSmartPointer<vtkXMLCollectionReader>::New();
    m_compositeFilter = vtkSmartPointer<vtkCompositeDataGeometryFilter>::New();
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
    m_interactor->Initialize();
    
    m_scene->Play();

    m_interactor->Start();
  }

  void Visualiser::extractTimeSteps() {

    m_reader->UpdateInformation();
    m_readerInfo = m_reader->GetOutputInformation( 0 ); // 0 indicating an output port
    
    #if( CSIM_DEBUG == 1 )
    if( m_readerInfo == nullptr ) {
      CSIM_M_DEBUG_LOG( "#CSIM# extractTimeSteps : m_readerInfo is null" );
    }
    #endif
    
    unsigned long long int totalTimeSteps = m_readerInfo->Length( vtkStreamingDemandDrivenPipeline::TIME_STEPS() );
    
    if( totalTimeSteps <= 0 ) {
      m_minTime = 0.0;
      m_maxTime = 0.0;

      return;
    }
    
    // Copying 
    std::vector<double> times;
    times.reserve( totalTimeSteps );

    for( unsigned long long int idx = 0; idx < totalTimeSteps; idx++ ) {
      times.push_back( m_readerInfo->Get( vtkStreamingDemandDrivenPipeline::TIME_STEPS(), idx ) );
    }

    auto [ tmpMinTime, tmpMaxTime ] = std::minmax_element( times.begin(), times.end() );
    m_minTime = *tmpMinTime;
    m_maxTime = *tmpMaxTime;

  }
  
  void CueCallback::Execute( vtkObject* caller, unsigned long eventId, void* callData ) {
    // Ensuring tick based response
    if( eventId != vtkCommand::AnimationCueTickEvent ) return;

    // Tbh I don't fully understand this but it seems common
    auto* cue = vtkAnimationCue::SafeDownCast( caller );

    const float time = cue->GetAnimationTime();

    m_filter->UpdateTimeStep( time );

    m_window->Render();
  }

}

#endif
