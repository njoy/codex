// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "codex/CovarianceBlock.hpp"

// namespace aliases
namespace python = pybind11;

void wrapCovarianceBlock( python::module& module ) {

  // type aliases
  using Component = njoy::codex::CovarianceBlock;
  using NuclideID = njoy::codex::NuclideID;
  using ReactionID = njoy::codex::NuclideID;
  using Matrix = njoy::codex::Matrix< double >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CovarianceBlock",
    "A covariance matrix block"
  );

  // wrap the component
  component
  .def(

    python::init< NuclideID, ReactionID, std::vector< double >, Matrix >(),
    python::arg( "nuclide" ), python::arg( "reaction" ),
    python::arg( "energies" ), python::arg( "matrix" ),
    "Initialise a diagonal covariance block\n\n"
    "Arguments:\n"
    "    self       the covariance block\n"
    "    nuclide    the nuclide identifier\n"
    "    reaction   the reaction identifier\n"
    "    energies   the energy boundaries\n"
    "    matrix     the covariance matrix"
  )
  .def(

    python::init< NuclideID, ReactionID, std::vector< double >,
                  NuclideID, ReactionID, std::vector< double >,
                  Matrix >(),
    python::arg( "row_nuclide" ), python::arg( "row_reaction" ),
    python::arg( "row_energies" ), python::arg( "column_nuclide" ),
    python::arg( "column_reaction" ), python::arg( "column_energies" ),
    python::arg( "matrix" ),
    "Initialise an off-diagonal covariance block\n\n"
    "Arguments:\n"
    "    self              the covariance block\n"
    "    row_nuclide       the row nuclide identifier\n"
    "    row_reaction      the row reaction identifier\n"
    "    row_energies      the row energy boundaries\n"
    "    column_nuclide    the row nuclide identifier\n"
    "    column_reaction   the row reaction identifier\n"
    "    column_energies   the row energy boundaries\n"
    "    matrix            the covariance matrix"
  )
  .def_property_readonly(

    "row_metadata",
    &Component::rowMetadata,
    "The row metadata"
  )
  .def_property_readonly(

    "column_metadata",
    &Component::columnMetadata,
    "The column metadata"
  )
  .def_property_readonly(

    "is_off_diagonal_block",
    &Component::isOffDiagonalBlock,
    "Flag to indicate whether or not this covariance block is an off-diagonal block"
  )
  .def_property_readonly(

    "is_diagonal_block",
    &Component::isDiagonalBlock,
    "Flag to indicate whether or not this covariance block is a diagonal block"
  )
  .def_property_readonly(

    // to ensure the matrix is not copied: reference_internal is used
    // see pybind11 documentation for Eigen bindings for more information

    "matrix",
    &Component::matrix,
    "The covariance matrix",
    python::return_value_policy::reference_internal
  );
}
