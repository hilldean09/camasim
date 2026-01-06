---
Created: 2025-12-11
---

Firstly, note the lack of progress in the last few days was due to studying VTK more thoroughly.

# VTK Guassian Splat Rendering
After studying VTK in more depth I have come to the following pipeline,
```cpp

#include <vtkActor.h>
#include <vtkDoubleArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPointGaussianMapper.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main() {
  
  // Colours
  vtkNew<vtkNamedColors> colors;
  colors->SetColor("ParaViewBkg",
                   std::array<unsigned char, 4>{82, 87, 110, 255}.data());

  // Setting up points
  auto points = vtkSmartPointer<vtkPoints>::New();

  points->InsertNextPoint( 0.0, 0.0, 0.0 );
  points->InsertNextPoint( 100.0, 0.0, 0.0 );
  points->InsertNextPoint( 0.0, 100.0, 0.0 );
  points->InsertNextPoint( 0.0, 0.0, 100.0 );

  // Setting up radii
  auto radii = vtkSmartPointer<vtkDoubleArray>::New();

  radii->SetName( "radii" );
  radii->SetNumberOfComponents( 1 );

  radii->InsertNextValue( 1.0 );
  radii->InsertNextValue( 2.0 );
  radii->InsertNextValue( 3.0 );
  radii->InsertNextValue( 4.0 );

  // Poly data
  auto polyData = vtkSmartPointer<vtkPolyData>::New();

  polyData->SetPoints( points );

  polyData->GetPointData()->AddArray( radii );
  polyData->GetPointData()->SetActiveScalars( "radii" );

  // Mapper
  auto mapper = vtkSmartPointer<vtkPointGaussianMapper>::New();
  
  mapper->SetInputData( polyData );
  mapper->SetScaleArray( "radii" );
  mapper->SetScaleArrayComponent( 0.0 );
  mapper->SetScaleFactor( 10.0 );
  
  // Actor propoerties
  vtkNew<vtkProperty> actorProperty;
  actorProperty->SetColor( colors->GetColor3d( "Peru" ).GetData() );

  // Actor
  auto actor = vtkSmartPointer<vtkActor>::New();

  actor->SetProperty( actorProperty );
  actor->SetMapper( mapper );

  // Render and window
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->GetBackground( colors->GetColor3d( "ParaViewBkg" ).GetData() );
  renderer->AddActor( actor );
  
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  renderWindow->SetSize( 800, 600 );

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( renderWindow );

  // Running
  renderWindow->Render();
  interactor->Initialize();
  interactor->Start();

  return 0;
}

```

The point insertion and update methods still need to be defined, however, this general pipeline will allow for initial rendering.