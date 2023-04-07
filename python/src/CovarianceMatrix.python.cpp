// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "codex/CovarianceMatrix.hpp"

// namespace aliases
namespace python = pybind11;

void wrapCovarianceMatrix( python::module& module ) {

  // type aliases
  using Component = njoy::codex::CovarianceMatrix;
  using CovarianceBlock = njoy::codex::CovarianceBlock;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CovarianceMatrix",
    "A covariance matrix composed from covariance blocks"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< CovarianceBlock > >(),
    python::arg( "blocks" ),
    "Initialise a diagonal covariance block\n\n"
    "Arguments:\n"
    "    self      the covariance matrix\n"
    "    blocks    the covariance blocks making up the matrix"
  )
  .def(

    "block",
    &Component::block,
    python::arg( "i" ), python::arg( "j" ),
    "Return a covariance block\n\n"
    "Arguments:\n"
    "    i    the row index of the block to retrieve\n"
    "    j    the column index of the block to retrieve"
  )
  .def(

    "metadata",
    &Component::metadata,
    python::arg( "i" ),
    "Return the metadata for a given row or column\n\n"
    "Arguments:\n"
    "    i    the index of the metadata to retrieve"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The covariance matrix order"
  )
  .def_property_readonly(

    "covariances",
    &Component::covariances,
    "The covariance matrix",
    python::return_value_policy::reference_internal
  );
}
