cmake_minimum_required( VERSION 4.2.0 )
project( camasim )

add_executable( main )

target_sources( main
  PRIVATE
    main.cpp
)

add_subdirectory( core )
