########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( codex
  VERSION 0.1.0
  LANGUAGES CXX
)

include( CTest )
include( CMakeDependentOption )
include( GNUInstallDirs )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

cmake_dependent_option(
  codex.tests
  "Build the codex unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)
cmake_dependent_option(
  codex.python
  "Build codex python bindings" ON
  "NOT ${subproject}" OFF
)

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

add_library( codex INTERFACE )
add_library( njoy::codex ALIAS codex )
target_include_directories( codex
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries( codex
  INTERFACE
    njoy::tools
    ENDFtk
    eigen
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# codex : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( codex.python )

  FetchContent_MakeAvailable( pybind11 )

  pybind11_add_module( codex.python
      python/src/codex.python.cpp
      python/src/matrix.python.cpp
      python/src/MetaData.python.cpp
      python/src/CovarianceBlock.python.cpp
      python/src/format.python.cpp
      python/src/format.endf.python.cpp
      )

  target_link_libraries( codex.python PRIVATE codex )
  target_include_directories( codex.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( codex.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( codex.python PROPERTIES OUTPUT_NAME codex )
  set_target_properties( codex.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( codex.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building codex's python API" )

  list( APPEND CODEX_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )

  include( cmake/unit_testing_python.cmake )

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( codex.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
