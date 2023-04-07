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

} // codex namespace
} // njoy namespace

#endif
