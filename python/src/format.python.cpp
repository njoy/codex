// system includes
#include <pybind11/pybind11.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace format {

  // declarations
  void wrapENDF( python::module& );
} // namespace format

/**
 *  @brief Wrap the format submodule
 *
 *  @param[in,out] module   the python module
 */
void wrapFormat( python::module& module ) {

    // create the format submodule
  python::module format = module.def_submodule(

    "format",
    "format - covariance formatting tools"
  );

  // wrap ENDF format functionality
  format::wrapENDF( format );
}
