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

    "row",
    &Component::row,
    "The row metadata"
  )
  .def_property_readonly(

    "column",
    &Component::column,
    "The column metadata"
  )
  .def_property_readonly(

    "is_off_diagonal",
    &Component::isOffDiagonal,
    "Flag to indicate whether or not this covariance block is an off-diagonal block"
  )
  .def_property_readonly(

    "is_diagonal",
    &Component::isDiagonal,
    "Flag to indicate whether or not this covariance block is a diagonal block"
  )
  .def_property_readonly(

    "covariances",
    &Component::covariances,
    "The covariance matrix",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "uncertainties",
    &Component::uncertainties,
    "The uncertainties",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "correlations",
    &Component::correlations,
    "The correlation matrix",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "eigenvalues",
    &Component::eigenvalues,
    "The eigenvalues",
    python::return_value_policy::reference_internal
  )
  .def(

    "calculate_uncertainties",
    &Component::calculateUncertainties,
    "Calculate the uncertainties from the covariances\n\n"
    "The uncertainties can only be calculated from covariance blocks on the\n"
    "diagonal of the covariance matrix. When this function is called on an\n"
    "off diagonal block, the function has no effect."
  )
  .def(

    "calculate_correlations",
    python::overload_cast<>( &Component::calculateCorrelations ),
    "Calculate the correlations (for covariance blocks on the diagonal)\n\n"
    "The correlations can only be calculated without input of the uncertainties\n"
    "for covariance blocks on the diagonal of the covariance matrix. When this\n"
    "method is called on an off diagonal block, the method has no effect.\n"
    "Uncertainties will be calculated and stored as well."
  )
  .def(

    "calculate_correlations",
    python::overload_cast<
        const std::vector< double >&,
        const std::vector< double >& >( &Component::calculateCorrelations ),
    python::arg( "row" ), python::arg( "column" ),
    "Calculate the uncertainties (for off diagonal covariance blocks)\n\n"
    "The correlations can only be calculated with input of the uncertainties\n"
    "for covariance blocks that are off diagonal in the covariance matrix.\n"
    "Uncertainties will not be stored.\n\n"
    "Arguments:\n"
    "    self      the covariance block\n"
    "    row       the uncertainties to be applied to each row\n"
    "    column    the uncertainties to be applied to each column"
  )
  .def(

    "calculate_eigenvalues",
    &Component::calculateEigenvalues,
    "Calculate the eigenvalues from the covariances\n\n"
    "The eigenvalues can only be calculated from covariance blocks on the\n"
    "diagonal of the covariance matrix. When this function is called on an\n"
    "off diagonal block, the function has no effect."
  );
}
