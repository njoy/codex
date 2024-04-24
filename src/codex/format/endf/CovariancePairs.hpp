#ifndef NJOY_CODEX_FROM_ENDF
#define NJOY_CODEX_FROM_ENDF

// system includes

// other includes
#include "tools/Log.hpp"
#include "ENDFtk/section/CovariancePairs.hpp"
#include "codex/CovarianceBlock.hpp"

namespace njoy {
namespace codex {
namespace format {

namespace endf {

  Matrix< double >
  matrix( const ENDFtk::section::CovariancePairs& endf ) {

    switch ( endf.procedure() ) {

      case 0 :
      case 1 : {

        unsigned int size = endf.numberPairs() - 1;
        Matrix< double > matrix( size, size );
        for ( unsigned int i = 0; i < size; ++i ) {

          matrix( i, i ) = endf.firstArrayFValues()[i];
        }
        return matrix;
      }
      default : {

        throw std::runtime_error( "not supported yet" );
      }
    }
  }
}

CovarianceBlock
fromENDF( NuclideID nuclide, ReactionID reaction,
          const ENDFtk::section::CovariancePairs& endf ) {

  std::vector< double > structure( endf.firstArrayEnergies().begin(),
                                   endf.firstArrayEnergies().end() );
  return CovarianceBlock( MetaData( nuclide, reaction, std::move( structure ) ),
                          endf::matrix( endf ),
                          endf.procedure() == 0 ? false : true );
}

} // formats namespace
} // codex namespace
} // njoy namespace

#endif
