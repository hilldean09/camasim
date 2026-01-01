
#ifndef CSIM_PRE_CONTROLS_HPP
#define CSIM_PRE_CONTROLS_HPP

#include <iostream>

// Debug
#define CSIM_DEBUG 1
#define CSIM_M_DEBUG_LOG( message ) std::cout << "#CSIM# " << message << std::endl
#define CSIM_M_DEBUG_CUDA_ERROR_LOG( cudaExpr, func, message ) if( ( cudaExpr )!= cudaSuccess ) { std::cout << "#CSIM# " << func << " : " << "CUDA error detected\n" << "\t" << message << std::endl; } 

// Logging
#define CSIM_VERBOSITY 2
#define CSIM_LOG_HEADER( func ) "[CSIM] " << func << " : "


/* 
* Ignore the unfortunate American spelling. Done for 
* consistency with VTK
*/
// Filesystem
#define CSIM_VTK_OUTPUT_DIRECTORY_NAME "csim_vtk_output"
#define CSIM_VTK_RADII_BINARY_NAME "radii.bin"

#define CSIM_VTK_FRAME_NUMBER_PADDING 6


// Rendering
#define CSIM_PARTICLE_COLOR "Peru"
#define CSIM_CENTRAL_BODY_COLOR "Maroon"
#define CSIM_BACKGROUND_COLOR "DarkSlateGray"

#define CSIM_USE_SCREEN_SIZE 1
#define CSIM_WINDOW_SIZE_X 800
#define CSIM_WINDOW_SIZE_Y 600

#define CSIM_POINT_SCALE_FACTOR 10.0


// CUDA
#define CSIM_USE_CUDA 1
#define CSIM_CUDA_THREADS_PER_BLOCK 256
#define CSIM_CUDA_BLOCKS 64 


// Octree 
#define CSIM_OCTANT_PARTICLE_CUTOFF 16
#define CSIM_OCTREE_BOUNDS_HALF_LENGTH 1'000'000'000'000


#endif
