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
  FiltersSources
  InteractionStyle
  InteractionWidgets
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "SphereSource: Unable to find the VTK build folder.")
endif()


add_executable( main )

target_sources( main
  PRIVATE
    main.cpp
)

add_subdirectory( core )

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS sphere_test 
  MODULES ${VTK_LIBRARIES}
)
