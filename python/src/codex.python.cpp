// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

int add( int i, int j ) {

    return i + j;
}

/**
 *  @brief codex python bindings
 *
 *  The name given here (codex) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( codex, module ) {

  module.def( "add", &add, "A function that adds two numbers" );
}
