#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "codex/matrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;

SCENARIO( "matrix functions" ) {

  Matrix< double > square_symmetric( 2, 2 );
  square_symmetric(0,0) = 1.;
  square_symmetric(0,1) = 2.;
  square_symmetric(1,0) = 2.;
  square_symmetric(1,1) = 4.;

  Matrix< double > square_notsymmetric( 2, 2 );
  square_notsymmetric(0,0) = 1.;
  square_notsymmetric(0,1) = 2.;
  square_notsymmetric(1,0) = 1000.;
  square_notsymmetric(1,1) = 4.;

  Matrix< double > notsquare( 3, 2 );
  notsquare(0,0) = 1.;
  notsquare(0,1) = 2.;
  notsquare(1,0) = 2.;
  notsquare(1,1) = 4.;
  notsquare(1,0) = 3.;
  notsquare(1,1) = 6.;

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
