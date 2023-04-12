// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "codex/MetaData.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMetaData( python::module& module ) {

  // type aliases
  using Component = njoy::codex::MetaData;
  using NuclideID = njoy::codex::NuclideID;
  using ReactionID = njoy::codex::NuclideID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MetaData",
    "Metadata for the rows or columns of a covariance matrix block"
  );

  // wrap the component
  component
  .def(

    python::init< NuclideID, ReactionID, std::vector< double > >(),
    python::arg( "nuclide" ), python::arg( "reaction" ), python::arg( "energies" ),
    "Initialise the meta data\n\n"
    "Arguments:\n"
    "    self       the meta data\n"
    "    nuclide    the nuclide identifier\n"
    "    reaction   the reaction identifier\n"
    "    energies   the energy boundaries"
  )
  .def_property_readonly(

    "nuclide",
    &Component::nuclide,
    "The nuclide identifier"
  )
  .def_property_readonly(

    "reaction",
    &Component::reaction,
    "The reaction identifier"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy boundaries"
  );
}
