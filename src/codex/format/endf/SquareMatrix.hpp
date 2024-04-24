#ifndef NJOY_CODEX_FROM_ENDF
#define NJOY_CODEX_FROM_ENDF

// system includes

// other includes
#include "tools/Log.hpp"
#include "ENDFtk/section/SquareMatrix.hpp"
#include "codex/CovarianceBlock.hpp"

namespace njoy {
namespace codex {
namespace format {

namespace endf {

  std::vector< double >
  structure( const ENDFtk::section::SquareMatrix& endf ) {

    return std::vector< double >( endf.energies().begin(), endf.energies().end() );
  }

  Matrix< double >
  matrix( const ENDFtk::section::SquareMatrix& endf ) {

    unsigned int size = endf.numberEnergies() - 1;
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
    return matrix;
  }
}

CovarianceBlock
fromENDF( NuclideID nuclide, ReactionID reaction,
          const ENDFtk::section::SquareMatrix& endf ) {

  return CovarianceBlock( MetaData( nuclide, reaction,
                          endf::structure( endf ) ),
                          endf::matrix( endf ) );
}

CovarianceBlock
fromENDF( NuclideID rowNuclide, ReactionID rowReaction,
          NuclideID columnNuclide, ReactionID columnReaction,
          const ENDFtk::section::SquareMatrix& endf ) {

    auto rowStructure = endf::structure( endf );
    auto columnStructure = rowStructure;
    return CovarianceBlock( MetaData( rowNuclide, rowReaction, std::move( rowStructure ) ),
                            MetaData( columnNuclide, columnReaction, std::move( columnStructure ) ),
                            endf::matrix( endf ) );
}

} // formats namespace
} // codex namespace
} // njoy namespace

#endif
