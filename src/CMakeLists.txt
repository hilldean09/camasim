cmake_minimum_required( VERSION 4.2.0 )
project( camasim )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic" )


# VTK
find_package( nlohmann_json REQUIRED )

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersSources
  InteractionStyle
  InteractionWidgets
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  IOXML
  IOParallelXML
  ParallelCore
  ParallelMPI
)

find_package( ParaView COMPONENTS VTKExtensionIOCore )

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Unable to find the VTK build folder.")
endif()


# Libraries
add_subdirectory( core )


# Main
add_executable( main )

target_sources( main
  PRIVATE
    main.cpp
)

target_link_libraries( main PRIVATE ${VTK_LIBRARIES} ParaView::VTKExtensionIOCore )


# Visualise
add_executable( visualise )

target_sources( visualise 
  PRIVATE
    visualise.cpp
)

target_link_libraries( visualise PRIVATE ${VTK_LIBRARIES} ParaView::VTKExtensionIOCore )


# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS main visualise
  MODULES ${VTK_LIBRARIES}
)
