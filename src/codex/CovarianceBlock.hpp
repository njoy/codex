#ifndef NJOY_CODEX_COVARIANCEBLOCK
#define NJOY_CODEX_COVARIANCEBLOCK

// system includes

// other includes
#include "tools/Log.hpp"
#include "codex/matrix.hpp"
#include "codex/MetaData.hpp"

namespace njoy {
namespace codex {

  /**
   *  @class
   *  @brief A covariance matrix block
   */
  class CovarianceBlock {

    /* fields - meta data */
    MetaData row_;
    std::optional< MetaData > column_;

    /* fields - covariance matrix */
    std::optional< Matrix< double > > covariances_;

    /* fields - standard deviations and correlations */
    std::optional< std::vector< double > > sigmas_;
    std::optional< Matrix< double > > correlations_;

    /* fields - eigenvalues */
    std::optional< std::vector< double > > eigenvalues_;

    /* auxiliary function */
    #include "codex/CovarianceBlock/src/verifyMatrix.hpp"
    #include "codex/CovarianceBlock/src/verifyStandardDeviations.hpp"

  public:

    /* constructor */
    #include "codex/CovarianceBlock/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the row metadata
     */
    const MetaData& rowMetadata() const { return this->row_; }

    /**
     *  @brief Return the column metadata
     */
    const MetaData& columnMetadata() const {

      if ( this->column_ ) {

        return this->column_.value();
      }
      else {

        return this->row_;
      }
    }

    /**
     *  @brief Return whether or not this covariance block is an off diagonal block
     */
    bool isOffDiagonalBlock() const {

      return bool( this->column_ );
    }

    /**
     *  @brief Return whether or not this covariance block is a diagonal block
     */
    bool isDiagonalBlock() const {

      return ! this->isOffDiagonalBlock();
    }

    /**
     *  @brief Return the covariance matrix
     */
    const std::optional< Matrix< double > >& covariances() const {

      return this->covariances_;
    }

    /**
     *  @brief Return the standard deviations
     */
    const std::optional< std::vector< double > >& standardDeviations() const {

      return this->sigmas_;
    }

    /**
     *  @brief Return the correlation matrix
     */
    const std::optional< Matrix< double > >& correlations() const {

      return this->correlations_;
    }

    /**
     *  @brief Return the eigenvalues
     */
    const std::optional< std::vector< double > >& eigenvalues() const {

      return this->eigenvalues_;
    }

    #include "codex/CovarianceBlock/src/calculateStandardDeviations.hpp"
    #include "codex/CovarianceBlock/src/calculateCorrelations.hpp"
    #include "codex/CovarianceBlock/src/calculateEigenvalues.hpp"
  };

} // codex namespace
} // njoy namespace

#endif
