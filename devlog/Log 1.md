---
Created: 2025-11-18
---

# Core
- The core of CAMASIM will be written as a library and utilised by the ```main.cpp```
- A ```Manager``` class will act as the central connection for all aspects of CAMASIM.
- The manager will include all other required objects (e.g. particles, central body, renderer, etc).
- The particle cloud and its initial conditions will be generated using deterministic seed based randomness functions
- Particles will be simulated by the ```Particle``` class and have their own dedicated management class called ```Particle_Cloud```.
- The central body will be simulated by the ```Central_Body``` class.
- The ```Central_Body``` and ```Particle``` classes will be derived from the base class ```Entity```.
- All contents will be kept under the ```Camasim``` namespace which will often be aliased to ```Csim```.
- Pre-processor controls will be included in a dedicated header file ```pre_controls.hpp```.
- GPU accelerated functionality for any given family of source files will be included in separate CUDA files named ```[Family Name]_gpua.cu```. Exceptional circumstances will be explicitly noted.
- The project will include ```PrecT``` as a common template type meant to represent any floating point type, allowing for easily variable levels of precision.

# Vector Struct
- The ```Vector``` struct will used to store the Cartesian coordinates of various vector values in the project.
- ```Vector``` will contain a method to calculate various values of the represented, including magnitude and the vector's radial representation.
- Note that the current method of calculating the absolute of the vector will utilise ```std::hypot```. As calculating vector magnitudes can be an expensive computation, this should be revisited during optimisation.