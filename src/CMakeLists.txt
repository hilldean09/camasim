cmake_minimum_required( VERSION 4.2.0 )
project( camasim )

add_executable( main PRIVATE main.cpp )

add_subdirectory( core )
