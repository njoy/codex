// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "codex/MetaData.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;

SCENARIO( "MetaData" ) {

  GIVEN( "valid data for a MetaData" ) {

    WHEN( "the data is given explicitly" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      MetaData chunk( std::move( nuclide ), std::move( reaction ),
                      std::move( energies ) );

      THEN( "a MetaData can be constructed and members can be tested" ) {

        CHECK( "U235" == chunk.nuclide() );
        CHECK( "elastic" == chunk.reaction() );

        CHECK( 4 == chunk.energies().size() );
        CHECK( 3 == chunk.numberGroups() );
        CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 1e+6, WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 2e+7, WithinRel( chunk.energies()[3] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a MetaData" ) {

    WHEN( "the energy grid does not have at least 2 elements" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > wrong = { 1e-5 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MetaData( std::move( nuclide ), std::move( reaction ),
                                std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "the energy grid is not sorted" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > wrong = { 2e+7, 1e+6, 1., 1e-5 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MetaData( std::move( nuclide ), std::move( reaction ),
                                std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "the energy grid has duplicate points" ) {

      NuclideID nuclide( "U235" );
      ReactionID reaction( "elastic" );
      std::vector< double > wrong = { 1e-5, 1., 1., 2e+7 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MetaData( std::move( nuclide ), std::move( reaction ),
                                std::move( wrong ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
