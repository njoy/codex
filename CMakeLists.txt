########################################################################
# Preamble
########################################################################
cmake_minimum_required( VERSION 3.14 )
project( codex LANGUAGES CXX )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( codex.tests "Build the codex unit tests" OFF )
option( codex.python "Build codex python bindings" ON )
option( strict_compile
    "Treat all warnings as errors." ON
    )

# Compile flags
set( common_flags "-Wall" "-Wextra" "-Wpedantic" )
set( strict_flags "-Werror" )
set( release_flags "-O3" )
set( debug_flags "-O0" "-g" )


########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

message( STATUS "Using ${REPOSITORIES} repositories" )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# codex : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

include_directories( src/ )

add_library( codex INTERFACE )
target_include_directories( codex INTERFACE src/ )
target_link_libraries( codex
    INTERFACE Log
    INTERFACE catch-adapter
    INTERFACE ENDFtk
    INTERFACE eigen
    )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# codex : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( codex.python )

  pybind11_add_module( codex.python
      python/src/codex.python.cpp
      python/src/matrix.python.cpp
      python/src/MetaData.python.cpp
      python/src/CovarianceBlock.python.cpp
      python/src/CovarianceMatrix.python.cpp
      )

  target_link_libraries( codex.python PRIVATE codex )
  target_include_directories( codex.python PRIVATE python/src )
  target_compile_options( codex.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( codex.python PROPERTIES OUTPUT_NAME codex )
  set_target_properties( codex.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( codex.python PROPERTIES POSITION_INDEPENDENT_CODE ON)

endif()

#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    if( codex.tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
