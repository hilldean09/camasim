cmake_minimum_required( VERSION 4.2.0 )
project( camasim )

set( CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++23" )

add_executable( main main.cpp )

target_sources( main 
  PRIVATE
    main.cpp

)

add_subdirectory( core )
