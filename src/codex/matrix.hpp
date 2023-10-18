#ifndef NJOY_CODEX_MATRIX
#define NJOY_CODEX_MATRIX

// system includes

// other includes
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

namespace njoy {
namespace codex {

  /* type aliases */
  template < typename T > using Matrix = Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic >;
  template < typename T > using DiagonalMatrix = Eigen::DiagonalMatrix< T, Eigen::Dynamic >;

  /* common matrix tests */

  /**
   *  @brief Return whether or not a matrix is square
   */
  template < typename T >
  bool isSquare( const Matrix< T >& matrix ) {

    return matrix.rows() == matrix.cols();
  }

  /**
   *  @brief Return whether or not a matrix is symmetric
   *
   *  Note: Eigen provides a default epsilon for the comparison. We can override
   *        that epsilon if need be.
   */
  template < typename T >
  bool isSymmetric( const Matrix< T >& matrix ) {

    return isSquare( matrix ) && matrix.isApprox( matrix.transpose() );
  }

} // codex namespace
} // njoy namespace

#endif