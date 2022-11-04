// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations
void wrapMetaData( python::module& );
void wrapCovarianceBlock( python::module& );

/**
 *  @brief codex python bindings
 *
 *  The name given here (codex) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( codex, module ) {

  // wrap covariance matrix components
  wrapMetaData( module );
  wrapCovarianceBlock( module );
}
