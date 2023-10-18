#ifndef NJOY_CODEX_METADATA
#define NJOY_CODEX_METADATA

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace codex {

  using NuclideID = std::string;
  using ReactionID = std::string;

  /**
   *  @class
   *  @brief Metadata for the rows or columns of a covariance matrix block
   */
  class MetaData {

    /* fields */
    NuclideID nuclide_;
    ReactionID reaction_;
    std::vector< double > energies_;

    /* auxiliary function */
    #include "codex/MetaData/src/verifyEnergies.hpp"

  public:

    /* constructor */
    #include "codex/MetaData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the nuclide identifier
     */
    const NuclideID& nuclide() const { return this->nuclide_; }

    /**
     *  @brief Return the reaction identifier
     */
    const ReactionID& reaction() const { return this->reaction_; }

    /**
     *  @brief Return the energy boundaries
     */
    const std::vector< double >& energies() const { return this->energies_; }

    /**
     *  @brief Return the number of energy groups
     */
    std::size_t numberGroups() const { return this->energies().size() - 1; }
  };

} // codex namespace
} // njoy namespace

#endif
