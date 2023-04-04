#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "codex/CovarianceBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;

SCENARIO( "CovarianceBlock" ) {

  GIVEN( "valid data for a diagonal CovarianceBlock" ) {

    NuclideID nuclide( "U235" );
    ReactionID reaction( "elastic" );
    std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

    Matrix< double > matrix( 3, 3 );
    matrix(0,0) = 1.;
    matrix(0,1) = 2.;
    matrix(0,2) = 3.;
    matrix(1,0) = 2.;
    matrix(1,1) = 4.;
    matrix(1,2) = 5.;
    matrix(2,0) = 3.;
    matrix(2,1) = 5.;
    matrix(2,2) = 6.;

    CovarianceBlock chunk( std::move( nuclide ), std::move( reaction ),
                           std::move( energies ), std::move( matrix ) );

    THEN( "a MetaData can be constructed and members can be tested" ) {

      CHECK( "U235" == chunk.row().nuclide() );
      CHECK( "elastic" == chunk.row().reaction() );
      CHECK( 4 == chunk.row().energies().size() );
      CHECK( 3 == chunk.row().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.row().energies()[0] ) );
      CHECK( 1.   == Approx( chunk.row().energies()[1] ) );
      CHECK( 1e+6 == Approx( chunk.row().energies()[2] ) );
      CHECK( 2e+7 == Approx( chunk.row().energies()[3] ) );

      CHECK( "U235" == chunk.column().nuclide() );
      CHECK( "elastic" == chunk.column().reaction() );
      CHECK( 4 == chunk.column().energies().size() );
      CHECK( 3 == chunk.column().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.column().energies()[0] ) );
      CHECK( 1.   == Approx( chunk.column().energies()[1] ) );
      CHECK( 1e+6 == Approx( chunk.column().energies()[2] ) );
      CHECK( 2e+7 == Approx( chunk.column().energies()[3] ) );

      CHECK( false == chunk.isOffDiagonal() );
      CHECK( true == chunk.isDiagonal() );

      CHECK( 3 == chunk.covariances().rows() );
      CHECK( 3 == chunk.covariances().cols() );
      CHECK( 1. == chunk.covariances()(0,0) );
      CHECK( 2. == chunk.covariances()(0,1) );
      CHECK( 3. == chunk.covariances()(0,2) );
      CHECK( 2. == chunk.covariances()(1,0) );
      CHECK( 4. == chunk.covariances()(1,1) );
      CHECK( 5. == chunk.covariances()(1,2) );
      CHECK( 3. == chunk.covariances()(2,0) );
      CHECK( 5. == chunk.covariances()(2,1) );
      CHECK( 6. == chunk.covariances()(2,2) );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an off-diagonal CovarianceBlock" ) {

    NuclideID rowNuclide( "U235" );
    ReactionID rowReaction( "elastic" );
    std::vector< double > rowEnergies = { 1e-5, 1., 1e+6, 2e+7 };
    NuclideID columnNuclide( "U238" );
    ReactionID columnReaction( "fission" );
    std::vector< double > columnEnergies = { 1e-5, 2., 2e+7 };

    Matrix< double > matrix( 3, 2 );
    matrix(0,0) = 1.;
    matrix(0,1) = 2.;
    matrix(1,0) = 3.;
    matrix(1,1) = 4.;
    matrix(2,0) = 5.;
    matrix(2,1) = 6.;

    CovarianceBlock chunk( std::move( rowNuclide ),
                           std::move( rowReaction ),
                           std::move( rowEnergies ),
                           std::move( columnNuclide ),
                           std::move( columnReaction ),
                           std::move( columnEnergies ),
                           std::move( matrix ) );

    THEN( "a MetaData can be constructed and members can be tested" ) {

      CHECK( "U235" == chunk.row().nuclide() );
      CHECK( "elastic" == chunk.row().reaction() );
      CHECK( 4 == chunk.row().energies().size() );
      CHECK( 3 == chunk.row().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.row().energies()[0] ) );
      CHECK( 1.   == Approx( chunk.row().energies()[1] ) );
      CHECK( 1e+6 == Approx( chunk.row().energies()[2] ) );
      CHECK( 2e+7 == Approx( chunk.row().energies()[3] ) );

      CHECK( "U238" == chunk.column().nuclide() );
      CHECK( "fission" == chunk.column().reaction() );
      CHECK( 3 == chunk.column().energies().size() );
      CHECK( 2 == chunk.column().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.column().energies()[0] ) );
      CHECK( 2.   == Approx( chunk.column().energies()[1] ) );
      CHECK( 2e+7 == Approx( chunk.column().energies()[2] ) );

      CHECK( true == chunk.isOffDiagonal() );
      CHECK( false == chunk.isDiagonal() );

      CHECK( 3 == chunk.covariances().rows() );
      CHECK( 2 == chunk.covariances().cols() );
      CHECK( 1. == chunk.covariances()(0,0) );
      CHECK( 2. == chunk.covariances()(0,1) );
      CHECK( 3. == chunk.covariances()(1,0) );
      CHECK( 4. == chunk.covariances()(1,1) );
      CHECK( 5. == chunk.covariances()(2,0) );
      CHECK( 6. == chunk.covariances()(2,1) );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a CovarianceBlock" ) {

    WHEN( "the matrix is not square for a diagonal covariance block" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      Matrix< double > matrix( 3, 2 );
      matrix(0,0) = 1.;
      matrix(0,1) = 2.;
      matrix(1,0) = 3.;
      matrix(1,1) = 4.;
      matrix(2,0) = 5.;
      matrix(2,1) = 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceBlock( std::move( nuclide ),
                                       std::move( reaction ),
                                       std::move( energies ),
                                       std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for a diagonal covariance block" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > energies = { 1e-5, 1., 2e+7 };

      Matrix< double > matrix( 3, 3 );
      matrix(0,0) = 1.;
      matrix(0,1) = 2.;
      matrix(0,2) = 3.;
      matrix(1,0) = 2.;
      matrix(1,1) = 4.;
      matrix(1,2) = 5.;
      matrix(2,0) = 3.;
      matrix(2,1) = 5.;
      matrix(2,2) = 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceBlock( std::move( nuclide ),
                                       std::move( reaction ),
                                       std::move( energies ),
                                       std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for an off-diagonal covariance block (rows)" ) {

      NuclideID rowNuclide( "U235" );
      ReactionID rowReaction( "elastic" );
      std::vector< double > rowEnergies = { 1e-5, 1., 2e+7 };
      NuclideID columnNuclide( "U238" );
      ReactionID columnReaction( "fission" );
      std::vector< double > columnEnergies = { 1e-5, 2., 2e+7 };

      Matrix< double > matrix( 3, 2 );
      matrix(0,0) = 1.;
      matrix(0,1) = 2.;
      matrix(1,0) = 3.;
      matrix(1,1) = 4.;
      matrix(2,0) = 5.;
      matrix(2,1) = 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceBlock( std::move( rowNuclide ),
                                       std::move( rowReaction ),
                                       std::move( rowEnergies ),
                                       std::move( columnNuclide ),
                                       std::move( columnReaction ),
                                       std::move( columnEnergies ),
                                       std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for an off-diagonal covariance block (rows)" ) {

      NuclideID rowNuclide( "U235" );
      ReactionID rowReaction( "elastic" );
      std::vector< double > rowEnergies = { 1e-5, 1., 1e+6, 2e+7 };
      NuclideID columnNuclide( "U238" );
      ReactionID columnReaction( "fission" );
      std::vector< double > columnEnergies = { 1e-5, 2e+7 };

      Matrix< double > matrix( 3, 2 );
      matrix(0,0) = 1.;
      matrix(0,1) = 2.;
      matrix(1,0) = 3.;
      matrix(1,1) = 4.;
      matrix(2,0) = 5.;
      matrix(2,1) = 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceBlock( std::move( rowNuclide ),
                                       std::move( rowReaction ),
                                       std::move( rowEnergies ),
                                       std::move( columnNuclide ),
                                       std::move( columnReaction ),
                                       std::move( columnEnergies ),
                                       std::move( matrix ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
