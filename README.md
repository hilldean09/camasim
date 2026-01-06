# CAMASIM
Celestial Angular Momentum Averaging Simulation (CAMASIM) aims to simulate the formation of celestial discs through the process of averaging / aligning angular momentum within the system.

CAMASIM is currently still in development with imminent improvements including:
- Barnes-Hut gravity simulation,
- More accurate collision formula / process (current is inaccurate), and
- VTK video file output.

# Build
CAMASIM uses CMake for it's build system. To generate build files, use CMake to build the ```src``` directory, then use your build system of choice to build the ```main``` and ```visualise``` executables. The build type is set to "Release" by default, however, should you wish to, include the command line flag ```-DCMAKE_BUILD_TYPE=``` followed by either ```Release``` or ```Debug``` to select the build configuration. 

Note that CAMASIM as of currently requires a number of dependencies, and has also not yet been tested for Windows or ARM architectures, only x86_64 linux. Portability is currently lacking and improvements such as app-images will be included in the future.

# Configuration
CAMASIM's configuration is not yet refined, however, can be done via modifying values in ```src/main.cpp``` and ```src/core/pre_controls.hpp``` (Note, ```pre_controls.hpp``` refers to pre-processor controls). Verbosity can be modified in ```pre_controls.hpp``` with values between 0 and 7, though 2 is recommended. This system has also not yet been refined.

Configuration requires re-compilation.

# Usage
To use CAMASIM, first run the ```main``` executable until complete, making sure the "Interpretation complete" message has appeared, this will generate two a file and a subdirectory named ```csim_binary_output_...``` and ```csim_vtk_output_...``` respectively (the ellipsis represent the timestamp).

>[!warning] Output File Sizes
>In large simulation, or simulations with highly frequent sampling, the output data can easily exceed hundreds of gigabytes if not careful, the ```csim_vtk_output_...``` subdirectory in particular (even using appendix encoding). The default values will not produce this result.

To visualise the simulation run the ```visualise``` executable followed by the path to any ```csim_simulation.pvd``` file contained with the ```cim_vtk_output_...``` directory. The command will usually look like,
```bash
./visualise csim_vtk_output_[TIMESTAMP]/csim_simulation.pvd
```

After that, enjoy the show, when the animation stops you can move the camera to more closely inspect the final state.

# Screenshots
Twenty thousand particle simulation:
<img width="1038" height="933" alt="twenty_thousand_particles" src="https://github.com/user-attachments/assets/4ed5b3eb-7227-4407-9cfa-cc04ef24a74d" />


Ten million (I think) particle simulation:
<img width="1083" height="1017" alt="ten_million_particles" src="https://github.com/user-attachments/assets/46d73ef3-d544-471c-9f5d-35bb0c64c2c3" />

An exaggerated demonstration of particle collisions:
<img width="1480" height="735" alt="collision_chaos" src="https://github.com/user-attachments/assets/96100ba2-d8b0-462a-8c2b-c3108b784e47" />
