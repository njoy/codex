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
     *  @brief Return a covariance block
     *
     *  @param i    the row index of the block to retrieve
     *  @param j    the column index of the block to retrieve
     */
    const CovarianceBlock& block( std::size_t i, std::size_t j ) const {

      //! @todo handle off diagonal and check range?
      if ( i != j ) throw std::exception();
      return this->blocks_[this->diagonal_[i]];
    }

    /**
     *  @brief Return a covariance block
     *
     *  @param i    the row index of the block to retrieve
     *  @param j    the column index of the block to retrieve
     */
    CovarianceBlock& block( std::size_t i, std::size_t j ) {

      //! @todo handle off diagonal and check range?
      if ( i != j ) throw std::exception();
      return this->blocks_[this->diagonal_[i]];
    }

    /**
     *  @brief Return the metadata for a given row
     *
     *  @param i    the row index of the metadata to retrieve
     */
    const MetaData& row( std::size_t i ) const {

      //! @todo check range?
      return this->blocks_[this->diagonal_[i]].row();
    }

    /**
     *  @brief Return the metadata for a given column
     *
     *  @param i    the column index of the metadata to retrieve
     */
    const MetaData& column( std::size_t i ) const {

      //! @todo check range?
      return this->blocks_[this->diagonal_[i]].column();
    }

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
