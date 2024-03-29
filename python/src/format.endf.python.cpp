// system includes
#include <pybind11/pybind11.h>

// local includes
#include "codex/CovarianceBlock.hpp"
#include "codex/format/endf/SquareMatrix.hpp"

// namespace aliases
namespace python = pybind11;

namespace format {

  /**
   *  @brief Wrap the format submodule
   *
   *  @param[in,out] module   the python module
   */
  void wrapENDF( python::module& module ) {

      // create the endf submodule
    python::module endf = module.def_submodule(

      "format",
      "format - covariance formatting tools"
    );

    module
    .def( "from_endf",
          python::overload_cast< njoy::codex::NuclideID, njoy::codex::ReactionID,
                                 const njoy::ENDFtk::section::SquareMatrix& >( &njoy::codex::format::fromENDF ),
          python::arg( "nuclide" ), python::arg( "reaction" ), python::arg( "endf" ),
          "Return a CovarianceBlock from an ENDF SquareMatrix component" )
    .def( "from_endf",
          python::overload_cast< njoy::codex::NuclideID, njoy::codex::ReactionID,
                                 njoy::codex::NuclideID, njoy::codex::ReactionID,
                                 const njoy::ENDFtk::section::SquareMatrix& >( &njoy::codex::format::fromENDF ),
          python::arg( "row_nuclide" ), python::arg( "row_reaction" ),
          python::arg( "column_nuclide" ), python::arg( "column_reaction" ),
          python::arg( "endf" ),
          "Return a CovarianceBlock from an ENDF SquareMatrix component" );
  }
} // namespace format
