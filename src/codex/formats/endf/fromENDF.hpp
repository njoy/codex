#ifndef NJOY_CODEX_FROMENDF
#define NJOY_CODEX_FROMENDF

// system includes

// other includes
#include "tools/Log.hpp"
#include "ENDFtk/section/SquareMatrix.hpp"
#include "codex/CovarianceBlock.hpp"

namespace njoy {
namespace codex {
namespace formats {

  CovarianceBlock
  fromENDF( NuclideID nuclide, ReactionID reaction,
            const ENDFtk::section::SquareMatrix& endf ) {

    // group structure used for the matrix
    std::vector< double > energies( endf.energies().begin(),
                                    endf.energies().end() );

    // covariance matrix
    unsigned int size = energies.size() - 1;
    Matrix< double > matrix( size, size );
    unsigned int index = 0;
    if ( endf.isSymmetric() ) {

      for ( unsigned int i = 0; i < size; ++i ) {

        for ( unsigned int j = i; j < size; ++j ) {

          matrix( i, j ) = endf.values()[ index++ ];
          if ( i != j ) {

            matrix( j, i ) = matrix( i, j );
          }
        }
      }
    }
    else {

      for ( unsigned int i = 0; i < size; ++i ) {

        for ( unsigned int j = 0; j < size; ++j ) {

          matrix( i, j ) = endf.values()[ index++ ];
        }
      }
    }

    return CovarianceBlock( MetaData( nuclide, reaction, std::move( energies ) ),
                            std::move( matrix ) );
  }

} // formats namespace
} // codex namespace
} // njoy namespace

#endif
