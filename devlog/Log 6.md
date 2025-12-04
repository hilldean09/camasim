---
Created: 2025-12-03
---

# ```Recorder``` Output Structure Decision
In reference to [[Log 5#```Recorder``` File Output|Log 5]] the current (and hopefully finalised) output structure will be as follows. The "output header" will contain the information needed to interpret the file, bar the real number type used, in the order:
```
[Particle Number], [Frames Total], [Step], [Radii]
```

Frame data was chosen to be represented as,
```
[X-Positions], [Y-Positions], [Z-Positions]
```
To reduce the amount of "zippering" needing to be done during the simulation.

# Graphics Library Choice
I have chosen to use VTK as I am equally unfamiliar with all available graphics libraries besides Maplotlib and it appears to be, at the very least, common in scientific computing.

# [VTK Textbook](https://gitlab.kitware.com/vtk/textbook/raw/master/VTKBook/VTKTextBook.pdf) Notes
As the VTK textbook is rather dense, I will consolidate my notes here.

**Chapter 3**:
- Image-order vs object-order
- Flat and Gourand lighting (p.g. 55)
- ```vtkRenderWindow```, ```vtkRenderer```, ```vtkLight```, ```vtkCamera```, ```vtkActor```, ```vtkMapper```, ```vtkRenderWindowInteractor``` (p.g.74)
- ```vtkNew```, ```vtkSmartPointer```, ```vtkDelete``` for VTK object creation (p.g.75)
- See page 76 for ```vtkSmartPointer``` VTK object array creation and handling

# VTK General Notes
- [Point generation](https://examples.vtk.org/site/Cxx/GeometricObjects/Point/)
- Using imposter sphere mappers to maintain performance through the pipeline (```vtkPointGaussianMapper``` seems like a decent choice). [Researched with ChatGPT](https://chatgpt.com). 