#ifndef NJOY_CODEX_COVARIANCEMATRIX
#define NJOY_CODEX_COVARIANCEMATRIX

// system includes
#include <map>
#include <vector>

// other includes
#include "Log.hpp"
#include "codex/matrix.hpp"
#include "codex/CovarianceBlock.hpp"

namespace njoy {
namespace codex {

  /**
   *  @class
   *  @brief A covariance matrix composed from covariance blocks
   */
  class CovarianceMatrix {

    /* fields - covariance blocks */
    std::vector< CovarianceBlock > blocks_;

    /* fields - block indices */
    std::vector< std::size_t > diagonal_;

    /* fields - composed covariances, correlations, eigenvalues, etc. */
    Matrix< double > covariances_;

    /* auxiliary function */
    #include "codex/CovarianceMatrix/src/getDiagonalBlockIndices.hpp"
    #include "codex/CovarianceMatrix/src/constructCovarianceMatrix.hpp"

  public:

    /* constructor */
    #include "codex/CovarianceMatrix/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the covariance matrix order
     */
    std::size_t order() const {

      return this->covariances_.rows();
    }

    /**
     *  @brief Return the covariance matrix
     */
    const Matrix< double >& covariances() const {

      return this->covariances_;
    }

  };

} // codex namespace
} // njoy namespace

#endif
