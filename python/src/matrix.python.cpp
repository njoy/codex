// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "codex/CovarianceBlock.hpp"

// namespace aliases
namespace python = pybind11;

/**
 *  @brief Wrap a BasicBidirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename T >
void wrapMatrixFunctionsFor( python::module& module ) {

  module
  .def( "is_square",
        [] ( const njoy::codex::Matrix< T >& matrix )
           { return njoy::codex::isSquare( matrix ); },
        "Return whether or not a matrix is square" )
  .def( "is_symmetric",
        [] ( const njoy::codex::Matrix< T >& matrix )
           { return njoy::codex::isSymmetric( matrix ); },
        "Return whether or not a matrix is symmetric" );
}

void wrapMatrixFunctions( python::module& module ) {

  wrapMatrixFunctionsFor< double >( module );
}
