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
    matrix(0,0) = 1.;
    matrix(0,1) = 2.;
    matrix(0,2) = 3.;
    matrix(1,0) = 2.;
    matrix(1,1) = 4.;
    matrix(1,2) = 6.;
    matrix(2,0) = 3.;
    matrix(2,1) = 6.;
    matrix(2,2) = 9.;

    CovarianceBlock chunk( std::move( nuclide ), std::move( reaction ),
                           std::move( energies ), std::move( matrix ) );

    THEN( "a CovarianceBlock can be constructed and members can be tested" ) {

      CHECK( "U235" == chunk.rowMetadata().nuclide() );
      CHECK( "elastic" == chunk.rowMetadata().reaction() );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK( 3 == chunk.rowMetadata().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.rowMetadata().energies()[0] ) );
      CHECK( 1.   == Approx( chunk.rowMetadata().energies()[1] ) );
      CHECK( 1e+6 == Approx( chunk.rowMetadata().energies()[2] ) );
      CHECK( 2e+7 == Approx( chunk.rowMetadata().energies()[3] ) );

      CHECK( "U235" == chunk.columnMetadata().nuclide() );
      CHECK( "elastic" == chunk.columnMetadata().reaction() );
      CHECK( 4 == chunk.columnMetadata().energies().size() );
      CHECK( 3 == chunk.columnMetadata().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.columnMetadata().energies()[0] ) );
      CHECK( 1.   == Approx( chunk.columnMetadata().energies()[1] ) );
      CHECK( 1e+6 == Approx( chunk.columnMetadata().energies()[2] ) );
      CHECK( 2e+7 == Approx( chunk.columnMetadata().energies()[3] ) );

      CHECK( false == chunk.isOffDiagonalBlock() );
      CHECK( true == chunk.isDiagonalBlock() );

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.standardDeviations() );
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

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations can be calculated" ) {

      CHECK( std::nullopt != chunk.standardDeviations() );

      CHECK( 3 == chunk.standardDeviations().value().size() );
      CHECK( 1. == Approx( chunk.standardDeviations().value()[0] ) );
      CHECK( 2. == Approx( chunk.standardDeviations().value()[1] ) );
      CHECK( 3. == Approx( chunk.standardDeviations().value()[2] ) );
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
    matrix(0,0) = 1.;
    matrix(0,1) = 2.;
    matrix(1,0) = 2.;
    matrix(1,1) = 4.;
    matrix(2,0) = 3.;
    matrix(2,1) = 6.;

    CovarianceBlock chunk( std::move( rowNuclide ),
                           std::move( rowReaction ),
                           std::move( rowEnergies ),
                           std::move( columnNuclide ),
                           std::move( columnReaction ),
                           std::move( columnEnergies ),
                           std::move( matrix ) );

    THEN( "a CovarianceBlock can be constructed and members can be tested" ) {

      CHECK( "U235" == chunk.rowMetadata().nuclide() );
      CHECK( "elastic" == chunk.rowMetadata().reaction() );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK( 3 == chunk.rowMetadata().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.rowMetadata().energies()[0] ) );
      CHECK( 1.   == Approx( chunk.rowMetadata().energies()[1] ) );
      CHECK( 1e+6 == Approx( chunk.rowMetadata().energies()[2] ) );
      CHECK( 2e+7 == Approx( chunk.rowMetadata().energies()[3] ) );

      CHECK( "U238" == chunk.columnMetadata().nuclide() );
      CHECK( "fission" == chunk.columnMetadata().reaction() );
      CHECK( 3 == chunk.columnMetadata().energies().size() );
      CHECK( 2 == chunk.columnMetadata().numberGroups() );
      CHECK( 1e-5 == Approx( chunk.columnMetadata().energies()[0] ) );
      CHECK( 2.   == Approx( chunk.columnMetadata().energies()[1] ) );
      CHECK( 2e+7 == Approx( chunk.columnMetadata().energies()[2] ) );

      CHECK( true == chunk.isOffDiagonalBlock() );
      CHECK( false == chunk.isDiagonalBlock() );

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.standardDeviations() );
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

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations cannot be calculated" ) {

      CHECK( std::nullopt == chunk.standardDeviations() );
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

    WHEN( "the matrix is not symmetric for a diagonal covariance block" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      Matrix< double > matrix( 3, 3 );
      matrix(0,0) = 1.;
      matrix(0,1) = 2.;
      matrix(0,2) = 3.;
      matrix(1,0) = 2.;
      matrix(1,1) = 4.;
      matrix(1,2) = 6.;
      matrix(2,0) = 100000.;
      matrix(2,1) = 6.;
      matrix(2,2) = 9.;

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
          "for an off-diagonal covariance block (columns)" ) {

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
