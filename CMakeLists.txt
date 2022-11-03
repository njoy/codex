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

option( codex_unit_tests
    "Compile the codex unit tests and integrate with ctest" ON
    )
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

add_library( codex INTERFACE
    )
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

include_directories( python/src/ )

pybind11_add_module( codex.python
    EXCLUDE_FROM_ALL
    python/src/codex.python.cpp
    )
target_link_libraries( codex.python PRIVATE codex )
target_compile_options( codex.python PRIVATE "-fPIC" )
target_compile_options( codex.python PRIVATE "-fvisibility=hidden" )
set_target_properties( codex.python PROPERTIES OUTPUT_NAME codex )
set_target_properties( codex.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )

#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( codex_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()