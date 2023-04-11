#ifndef NJOY_CODEX_COVARIANCEBLOCK
#define NJOY_CODEX_COVARIANCEBLOCK

// system includes

// other includes
#include "Eigen/Core"
#include "Log.hpp"
#include "codex/MetaData.hpp"

namespace njoy {
namespace codex {

  /* type aliases */
  template < typename T > using Matrix = Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic >;
  template < typename T > using DiagonalMatrix = Eigen::DiagonalMatrix< T, Eigen::Dynamic >;

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

    /* fields - uncertainties and correlations */
    std::optional< std::vector< double > > uncertainties_;
    std::optional< Matrix< double > > correlations_;

    /* auxiliary function */
    #include "codex/CovarianceBlock/src/verifyMatrix.hpp"

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
     *  @brief Return the uncertainties
     */
    const std::optional< std::vector< double > >& uncertainties() const {

      return this->uncertainties_;
    }

    /**
     *  @brief Return the correlation matrix
     */
    const std::optional< Matrix< double > >& correlations() const {

      return this->correlations_;
    }

    #include "codex/CovarianceBlock/src/calculateUncertainties.hpp"
    #include "codex/CovarianceBlock/src/calculateCorrelations.hpp"
  };

} // codex namespace
} // njoy namespace

#endif
