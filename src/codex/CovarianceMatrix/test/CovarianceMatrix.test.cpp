#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "codex/CovarianceMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;

SCENARIO( "CovarianceMatrix" ) {

  GIVEN( "valid covariance blocks for a CovarianceMatrix" ) {

    Matrix< double > matrix00( 3, 3 );
    matrix00(0,0) = 1.;
    matrix00(0,1) = 2.;
    matrix00(0,2) = 3.;
    matrix00(1,0) = 2.;
    matrix00(1,1) = 4.;
    matrix00(1,2) = 6.;
    matrix00(2,0) = 3.;
    matrix00(2,1) = 6.;
    matrix00(2,2) = 9.;

    Matrix< double > matrix11( 2, 2 );
    matrix11(0,0) = 16.;
    matrix11(0,1) = 0.;
    matrix11(1,0) = 0.;
    matrix11(1,1) = 25.;

    std::vector< CovarianceBlock > blocks = {

      CovarianceBlock( NuclideID( "U235" ), ReactionID( "elastic" ),
                       { 1e-5, 1., 1e+6, 2e+7 },
                       std::move( matrix00 ) ),
      CovarianceBlock( NuclideID( "U235" ), ReactionID( "fission" ),
                       { 1e-5, 2., 2e+7 },
                       std::move( matrix11 ) )
    };

    CovarianceMatrix chunk( std::move( blocks ) );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 5 == chunk.order() );

      CHECK(  5 == chunk.covariances().rows() );
      CHECK(  5 == chunk.covariances().cols() );
      CHECK(  1. == chunk.covariances()(0,0) );
      CHECK(  2. == chunk.covariances()(0,1) );
      CHECK(  3. == chunk.covariances()(0,2) );
      CHECK(  0. == chunk.covariances()(0,3) );
      CHECK(  0. == chunk.covariances()(0,4) );
      CHECK(  2. == chunk.covariances()(1,0) );
      CHECK(  4. == chunk.covariances()(1,1) );
      CHECK(  6. == chunk.covariances()(1,2) );
      CHECK(  0. == chunk.covariances()(1,3) );
      CHECK(  0. == chunk.covariances()(1,4) );
      CHECK(  3. == chunk.covariances()(2,0) );
      CHECK(  6. == chunk.covariances()(2,1) );
      CHECK(  9. == chunk.covariances()(2,2) );
      CHECK(  0. == chunk.covariances()(2,3) );
      CHECK(  0. == chunk.covariances()(2,4) );
      CHECK(  0. == chunk.covariances()(3,0) );
      CHECK(  0. == chunk.covariances()(3,1) );
      CHECK(  0. == chunk.covariances()(3,2) );
      CHECK( 16. == chunk.covariances()(3,3) );
      CHECK(  0. == chunk.covariances()(3,4) );
      CHECK(  0. == chunk.covariances()(4,0) );
      CHECK(  0. == chunk.covariances()(4,1) );
      CHECK(  0. == chunk.covariances()(4,2) );
      CHECK(  0. == chunk.covariances()(4,3) );
      CHECK( 25. == chunk.covariances()(4,4) );
    } // THEN
  } // GIVEN
} // SCENARIO
