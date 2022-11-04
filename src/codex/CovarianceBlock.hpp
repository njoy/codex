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

  /**
   *  @class
   *  @brief A covariance matrix block
   */
  class CovarianceBlock {

    /* fields */
    MetaData row_;
    std::optional< MetaData > column_;
    Matrix< double > matrix_;

    /* auxiliary function */
    #include "codex/CovarianceBlock/src/verifyMatrix.hpp"

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
     *  @brief Return whether or not this covariance block is a diagonal block
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
    const Matrix< double >& matrix() const { return this->matrix_; }
  };

} // codex namespace
} // njoy namespace

#endif
