// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations
void wrapMatrixFunctions( python::module& );
void wrapMetaData( python::module& );
void wrapCovarianceBlock( python::module& );
void wrapCovarianceMatrix( python::module& );

/**
 *  @brief codex python bindings
 *
 *  The name given here (codex) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( codex, module ) {

  // wrap matrix functions
  wrapMatrixFunctions( module );

  // wrap covariance matrix components
  wrapMetaData( module );
  wrapCovarianceBlock( module );
  wrapCovarianceMatrix( module );
}
