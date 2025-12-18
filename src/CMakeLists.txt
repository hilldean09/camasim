cmake_minimum_required( VERSION 4.2.0 )
project( camasim )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic" )


find_package( Python3 REQUIRED COMPONENTS Development Development.Module )
find_package( CLI11 CONFIG REQUIRED )
find_package( Viskores CONFIG REQUIRED )
find_package( X11 REQUIRED )
find_package( Freetype REQUIRED )
find_package( MPI )

# VTK
find_package( nlohmann_json REQUIRED )

find_package( ParaView REQUIRED COMPONENTS VTKExtensionsIOCore )

set( CSIM_VTK_MODULES 
  VTK::CommonColor
  VTK::CommonCore
  VTK::CommonDataModel
  VTK::CommonMPI
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


# Libraries
add_subdirectory( core )


# Main
add_executable( main )

target_sources( main
  PRIVATE
    main.cpp
)

target_link_libraries( main PRIVATE 
  ParaView::VTKExtensionsIOCore 
  MPI::MPI_CXX
  ${CSIM_VTK_MODULES}
)


# Visualise
add_executable( visualise )

target_sources( visualise 
  PRIVATE
    visualise.cpp
)

target_link_libraries( visualise PRIVATE 
  ParaView::VTKExtensionsIOCore 
  MPI::MPI_CXX
  ${CSIM_VTK_MODULES}
)


# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS main visualise
  MODULES ${VTK_LIBRARIES}
)
