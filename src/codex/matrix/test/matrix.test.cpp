#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "codex/matrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;

SCENARIO( "matrix functions" ) {

  Matrix< double > square_symmetric( 2, 2 );
  square_symmetric << 1., 2.,
                      2., 4.;

  Matrix< double > square_notsymmetric( 2, 2 );
  square_notsymmetric << 1., 2.,
                      1000., 4.;

  Matrix< double > notsquare( 3, 2 );
  notsquare << 1., 2.,
               2., 4.,
               3., 6.;

  GIVEN( "isSquare" ) {

    CHECK( true == njoy::codex::isSquare( square_symmetric ) );
    CHECK( true == njoy::codex::isSquare( square_notsymmetric ) );
    CHECK( false == njoy::codex::isSquare( notsquare ) );
  } // GIVEN

  GIVEN( "isSymmetric" ) {

    CHECK( true == njoy::codex::isSymmetric( square_symmetric ) );
    CHECK( false == njoy::codex::isSymmetric( square_notsymmetric ) );
    CHECK( false == njoy::codex::isSymmetric( notsquare ) );
  } // GIVEN
} // SCENARIO
