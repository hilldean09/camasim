
#ifndef CSIM_INTERPRETER_TPP
#define CSIM_INTERPRETER_TPP

#include "pre_controls.hpp"
#include "structs.hpp"

#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCommand.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkInformation.h>
#include <vtkNamedColors.h>
#include <vtkObject.h>
#include <vtkPointGaussianMapper.h>
#include <vtkProperty.h>
#include <vtkPVDReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkXMLCollectionReader.h>

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

namespace CSIM {

  // Constructors //
  Visualiser::Visualiser() {
    initDefaults();
  }

  // Initialisers //
  void Visualiser::initialise( std::string collectionFile ) {
    #if( CSIM_DEBUG == 1 )
    m_reader->SetAbortExecute( 0 );

    if( !std::filesystem::exists( collectionFile.c_str() ) ) {
      CSIM_M_DEBUG_LOG( "#CSIM# initialise : file does not exist" );
    }
    #endif

    m_reader->SetFileName( collectionFile.c_str() );
    m_reader->Update();
    m_reader->UpdateInformation();

    extractTimeSteps();

    // Configuring
    m_pointMapper->SetInputConnection( m_reader->GetOutputPort() );
    m_pointMapper->SetScaleArray( "Radii" );
    m_pointMapper->SetScaleArrayComponent( 0 );
    m_pointMapper->SetScaleFactor( CSIM_POINT_SCALE_FACTOR );

    m_pointProperty->SetColor( m_colors->GetColor3d( CSIM_PARTICLE_COLOR ).GetData() );

    m_pointActor->SetMapper( m_pointMapper );
    m_pointActor->SetProperty( m_pointProperty );

    m_renderer->AddActor( m_pointActor );
    m_renderer->GetBackground( m_colors->GetColor3d( CSIM_BACKGROUND_COLOR ).GetData() );

    m_window->AddRenderer( m_renderer );
    m_window->SetSize( 800, 600 );

    m_interactor->SetRenderWindow( m_window );

    m_scene->SetModeToSequence();
    m_scene->SetFrameRate( 60 );
    m_scene->SetStartTime( m_minTime );
    m_scene->SetEndTime( m_maxTime );
    m_scene->AddCue( m_cue );

    m_callback->setRenderWindow( m_window );
    m_callback->setReader( m_reader );
    m_callback->setReaderInfo( m_readerInfo = m_reader->GetOutputInformation( 0 ) );

    m_cue->SetStartTime( m_minTime );
    m_cue->SetEndTime( m_maxTime );
    m_cue->AddObserver( vtkCommand::AnimationCueTickEvent, m_callback );
  }

  void Visualiser::initDefaults() {
    #if( CSIM_DEBUG == 1 )
    vtkObject::GlobalWarningDisplayOn();
    #endif

    m_colors = vtkSmartPointer<vtkNamedColors>::New();

    m_reader = vtkSmartPointer<vtkPVDReader>::New();
    m_pointMapper = vtkSmartPointer<vtkPointGaussianMapper>::New();

    m_pointActor = vtkSmartPointer<vtkActor>::New();
    m_pointProperty = vtkSmartPointer<vtkProperty>::New();

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
    if( !( m_readerInfo->Has( vtkStreamingDemandDrivenPipeline::TIME_STEPS() ) ) ) {
      CSIM_M_DEBUG_LOG( "#CSIM# extractTimeSteps : m_readerInfo has no TIME_STEPS()" );
    }
    #endif
    
    unsigned long long int totalTimeSteps = m_readerInfo->Length( vtkStreamingDemandDrivenPipeline::TIME_STEPS() );
    
    #if( CSIM_DEBUG == 1)
    CSIM_M_DEBUG_LOG( "#CSIM# extractTimeSteps : \n\ttotalTimeSteps : " << std::to_string( totalTimeSteps ) );
    #endif

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

    m_readerInfo->Set( vtkStreamingDemandDrivenPipeline::UPDATE_TIME_STEP(), time );
    m_reader->Update();

    m_window->Render();
  }

}

#endif
