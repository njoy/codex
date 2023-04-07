#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "codex/CovarianceBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;

SCENARIO( "CovarianceBlock" ) {

  GIVEN( "valid covariance data for a diagonal CovarianceBlock" ) {

    NuclideID nuclide( "U235" );
    ReactionID reaction( "elastic" );
    std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

    Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    CovarianceBlock chunk( std::move( nuclide ), std::move( reaction ),
                           std::move( energies ), std::move( matrix ) );

    THEN( "a CovarianceBlock can be constructed and members can be tested" ) {

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

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.uncertainties() );
      CHECK( std::nullopt == chunk.correlations() );
      CHECK( std::nullopt == chunk.eigenvalues() );

      CHECK( 3 == chunk.covariances().value().rows() );
      CHECK( 3 == chunk.covariances().value().cols() );
      CHECK( 1. == chunk.covariances().value()(0,0) );
      CHECK( 2. == chunk.covariances().value()(0,1) );
      CHECK( 3. == chunk.covariances().value()(0,2) );
      CHECK( 2. == chunk.covariances().value()(1,0) );
      CHECK( 4. == chunk.covariances().value()(1,1) );
      CHECK( 6. == chunk.covariances().value()(1,2) );
      CHECK( 3. == chunk.covariances().value()(2,0) );
      CHECK( 6. == chunk.covariances().value()(2,1) );
      CHECK( 9. == chunk.covariances().value()(2,2) );
    } // THEN

    chunk.calculateUncertainties();

    THEN( "Uncertainties can be calculated" ) {

      CHECK( std::nullopt != chunk.uncertainties() );

      CHECK( 3 == chunk.uncertainties().value().size() );
      CHECK( 1. == Approx( chunk.uncertainties().value()[0] ) );
      CHECK( 2. == Approx( chunk.uncertainties().value()[1] ) );
      CHECK( 3. == Approx( chunk.uncertainties().value()[2] ) );
    } // THEN

    chunk.calculateCorrelations();

    THEN( "Correlations can be calculated" ) {

      CHECK( std::nullopt != chunk.correlations() );

      CHECK( 3 == chunk.correlations().value().rows() );
      CHECK( 3 == chunk.correlations().value().cols() );
      CHECK( 1. == chunk.correlations().value()(0,0) );
      CHECK( 1. == chunk.correlations().value()(0,1) );
      CHECK( 1. == chunk.correlations().value()(0,2) );
      CHECK( 1. == chunk.correlations().value()(1,0) );
      CHECK( 1. == chunk.correlations().value()(1,1) );
      CHECK( 1. == chunk.correlations().value()(1,2) );
      CHECK( 1. == chunk.correlations().value()(2,0) );
      CHECK( 1. == chunk.correlations().value()(2,1) );
      CHECK( 1. == chunk.correlations().value()(2,2) );
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues can be calculated" ) {

      CHECK( std::nullopt != chunk.eigenvalues() );

      CHECK( 3 == chunk.eigenvalues().value().size() );
      CHECK( 0. == Approx( chunk.eigenvalues().value()[0] ) );
      CHECK( 0. == Approx( chunk.eigenvalues().value()[1] ) );
      CHECK( 14. == Approx( chunk.eigenvalues().value()[2] ) );
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
    matrix << 1., 2.,
              2., 4.,
              3., 6.;

    CovarianceBlock chunk( std::move( rowNuclide ),
                           std::move( rowReaction ),
                           std::move( rowEnergies ),
                           std::move( columnNuclide ),
                           std::move( columnReaction ),
                           std::move( columnEnergies ),
                           std::move( matrix ) );

    THEN( "a CovarianceBlock can be constructed and members can be tested" ) {

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

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.uncertainties() );
      CHECK( std::nullopt == chunk.correlations() );

      CHECK( 3 == chunk.covariances().value().rows() );
      CHECK( 2 == chunk.covariances().value().cols() );
      CHECK( 1. == chunk.covariances().value()(0,0) );
      CHECK( 2. == chunk.covariances().value()(0,1) );
      CHECK( 2. == chunk.covariances().value()(1,0) );
      CHECK( 4. == chunk.covariances().value()(1,1) );
      CHECK( 3. == chunk.covariances().value()(2,0) );
      CHECK( 6. == chunk.covariances().value()(2,1) );
    } // THEN

    chunk.calculateUncertainties();

    THEN( "Uncertainties cannot be calculated" ) {

      CHECK( std::nullopt == chunk.uncertainties() );
    } // THEN

    std::vector< double > row = { 1., 2., 3. };
    std::vector< double > column = { 1., 2. };
    chunk.calculateCorrelations( row, column );

    THEN( "Correlations can be calculated" ) {

      CHECK( std::nullopt != chunk.correlations() );

      CHECK( 3 == chunk.correlations().value().rows() );
      CHECK( 2 == chunk.correlations().value().cols() );
      CHECK( 1. == chunk.correlations().value()(0,0) );
      CHECK( 1. == chunk.correlations().value()(0,1) );
      CHECK( 1. == chunk.correlations().value()(1,0) );
      CHECK( 1. == chunk.correlations().value()(1,1) );
      CHECK( 1. == chunk.correlations().value()(2,0) );
      CHECK( 1. == chunk.correlations().value()(2,1) );
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues cannot be calculated" ) {

      CHECK( std::nullopt == chunk.eigenvalues() );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a CovarianceBlock" ) {

    WHEN( "the matrix is not square for a diagonal covariance block" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceBlock( std::move( nuclide ),
                                       std::move( reaction ),
                                       std::move( energies ),
                                       std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix is not symmetric for a diagonal covariance block" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 6.,
           100000., 6., 9.;

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
      matrix << 1., 2., 3.,
                2., 4., 5.,
                3., 5., 6.;

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
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

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
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

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
