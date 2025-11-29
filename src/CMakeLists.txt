cmake_minimum_required( VERSION 4.2.0 )
project( camasim )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic" )

add_executable( main )

target_sources( main
  PRIVATE
    main.cpp
)

add_subdirectory( core )
