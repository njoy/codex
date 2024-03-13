// system includes
#include <pybind11/pybind11.h>

// local includes
#include "codex/CovarianceBlock.hpp"
#include "codex/format/endf/fromENDF.hpp"

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

    // wrap ENDF format functionality
  }
} // namespace format
