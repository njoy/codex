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
    Matrix< double > matrix_;

    /* fields - uncertainties and correlations */
    std::optional< std::vector< double > > uncertainties_;
    std::optional< Matrix< double > > correlations_;

    /* auxiliary function */
    #include "codex/CovarianceBlock/src/verifyMatrix.hpp"
    #include "codex/CovarianceBlock/src/calculateUncertainties.hpp"
    #include "codex/CovarianceBlock/src/calculateCorrelations.hpp"

  public:

    /* constructor */
    #include "codex/CovarianceBlock/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the row metadata
     */
    const MetaData& row() const { return this->row_; }

    /**
     *  @brief Return the column metadata
     */
    const MetaData& column() const {

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
    bool isOffDiagonal() const {

      return bool( this->column_ );
    }

    /**
     *  @brief Return whether or not this covariance block is a diagonal block
     */
    bool isDiagonal() const {

      return !this->isOffDiagonal();
    }

    /**
     *  @brief Return the covariance matrix
     */
    const Matrix< double >& covariances() const { return this->matrix_; }

    /**
     *  @brief Return the uncertainties
     */
    const std::vector< double >& uncertainties() {

      this->calculateUncertainties();
      return this->uncertainties_.value();
    }

    /**
     *  @brief Return the correlation matrix
     */
    const Matrix< double >& correlations() {

      this->calculateCorrelations();
      return this->correlations_.value();
    }
  };

} // codex namespace
} // njoy namespace

#endif
