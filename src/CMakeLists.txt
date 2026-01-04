cmake_minimum_required( VERSION 4.2.0 )
project( camasim LANGUAGES C CXX CUDA )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( CMAKE_CUDA_STANDARD 20 )
set( CMAKE_CUDA_STANDARD_REQUIRED ON )
set( CMAKE_CUDA_EXTENSIONS OFF )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

set( CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic" )
set( CMAKE_CXX_FLAGS_DEBUG "-g" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )


find_package( Python3 REQUIRED COMPONENTS Development Development.Module )
find_package( CLI11 CONFIG REQUIRED )
find_package( Viskores CONFIG REQUIRED )
find_package( X11 REQUIRED )
find_package( Freetype REQUIRED )
find_package( MPI REQUIRED COMPONENTS C CXX )
find_package( OpenMP REQUIRED )

# VTK
find_package( nlohmann_json REQUIRED )

find_package( ParaView REQUIRED COMPONENTS VTKExtensionsIOCore )

set( CSIM_VTK_MODULES 
  VTK::CommonColor
  VTK::CommonCore
  VTK::CommonDataModel
  VTK::FiltersSources
  VTK::FiltersGeometry
  VTK::InteractionStyle
  VTK::InteractionWidgets
  VTK::RenderingContextOpenGL2
  VTK::RenderingCore
  VTK::RenderingFreeType
  VTK::RenderingGL2PSOpenGL2
  VTK::RenderingOpenGL2
  VTK::IOXML
  VTK::IOParallelXML
  VTK::ParallelCore
  VTK::ParallelMPI
)

set( CSIM_EXEC_MODULES 
  ParaView::VTKExtensionsIOCore 
  MPI::MPI_CXX
  OpenMP::OpenMP_CXX
  ${CSIM_VTK_MODULES}
)


# Libraries
add_subdirectory( core )

# Main
add_executable( main )

target_sources( main
  PRIVATE
    main.cpp
)

target_link_libraries( main PRIVATE 
  ${CSIM_EXEC_MODULES}
  csim_cuda
)


# Visualise
add_executable( visualise )

target_sources( visualise 
  PRIVATE
    visualise.cpp
)

target_link_libraries( visualise PRIVATE 
  ${CSIM_EXEC_MODULES}
)


# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS main visualise
  MODULES ${VTK_LIBRARIES}
)
