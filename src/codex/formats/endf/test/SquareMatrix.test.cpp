// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "codex/formats/endf/fromENDF.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;
using namespace njoy::ENDFtk;
using SquareMatrix = section::SquareMatrix;

std::string chunk();

SCENARIO( "SquareMatrix" ) {

  GIVEN( "an instance of SquareMatrix that is symmetric" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SquareMatrix endf( begin, end, lineNumber, 2231, 33, 16 );

    WHEN( "constructing a diagonal CovarianceBlock from a SquareMatrix" ) {

      CovarianceBlock chunk = formats::fromENDF( "Ti48", "n,2n", endf );

      THEN( "a CovarianceBlock can be created and members can be tested" ) {

        CHECK( "Ti48" == chunk.rowMetadata().nuclide() );
        CHECK( "n,2n" == chunk.rowMetadata().reaction() );
        CHECK( 11 == chunk.rowMetadata().energies().size() );
        CHECK( 10 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.187260e+7, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 1.300000e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 1.500000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk.rowMetadata().energies()[7] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.rowMetadata().energies()[8] ) );
        CHECK_THAT( 1.900000e+7, WithinRel( chunk.rowMetadata().energies()[9] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[10] ) );

        CHECK( "Ti48" == chunk.columnMetadata().nuclide() );
        CHECK( "n,2n" == chunk.columnMetadata().reaction() );
        CHECK( 11 == chunk.columnMetadata().energies().size() );
        CHECK( 10 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.187260e+7, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 1.300000e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 1.500000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk.rowMetadata().energies()[7] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.rowMetadata().energies()[8] ) );
        CHECK_THAT( 1.900000e+7, WithinRel( chunk.rowMetadata().energies()[9] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[10] ) );

        CHECK( false == chunk.isOffDiagonalBlock() );
        CHECK( true == chunk.isDiagonalBlock() );

        CHECK( std::nullopt != chunk.covariances() );
        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 10 == chunk.covariances().value().rows() );
        CHECK( 10 == chunk.covariances().value().cols() );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,7) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,8) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,0) ) );
        CHECK_THAT( 0.25, WithinRel( chunk.covariances().value()(1,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,7) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,8) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,1) ) );
        CHECK_THAT( 3.897788e-3, WithinRel( chunk.covariances().value()(2,2) ) );
        CHECK_THAT( 3.151794e-3, WithinRel( chunk.covariances().value()(2,3) ) );
        CHECK_THAT( 2.605989e-3, WithinRel( chunk.covariances().value()(2,4) ) );
        CHECK_THAT( 2.173942e-3, WithinRel( chunk.covariances().value()(2,5) ) );
        CHECK_THAT( 1.843332e-3, WithinRel( chunk.covariances().value()(2,6) ) );
        CHECK_THAT( 1.579267e-3, WithinRel( chunk.covariances().value()(2,7) ) );
        CHECK_THAT( 1.391836e-3, WithinRel( chunk.covariances().value()(2,8) ) );
        CHECK_THAT( 1.269227e-3, WithinRel( chunk.covariances().value()(2,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,1) ) );
        CHECK_THAT( 3.151794e-3, WithinRel( chunk.covariances().value()(3,2) ) );
        CHECK_THAT( 2.822801e-3, WithinRel( chunk.covariances().value()(3,3) ) );
        CHECK_THAT( 2.436598e-3, WithinRel( chunk.covariances().value()(3,4) ) );
        CHECK_THAT( 2.140176e-3, WithinRel( chunk.covariances().value()(3,5) ) );
        CHECK_THAT( 1.913301e-3, WithinRel( chunk.covariances().value()(3,6) ) );
        CHECK_THAT( 1.731503e-3, WithinRel( chunk.covariances().value()(3,7) ) );
        CHECK_THAT( 1.615025e-3, WithinRel( chunk.covariances().value()(3,8) ) );
        CHECK_THAT( 1.549830e-3, WithinRel( chunk.covariances().value()(3,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,1) ) );
        CHECK_THAT( 2.605989e-3, WithinRel( chunk.covariances().value()(4,2) ) );
        CHECK_THAT( 2.436598e-3, WithinRel( chunk.covariances().value()(4,3) ) );
        CHECK_THAT( 2.244027e-3, WithinRel( chunk.covariances().value()(4,4) ) );
        CHECK_THAT( 2.112649e-3, WithinRel( chunk.covariances().value()(4,5) ) );
        CHECK_THAT( 2.011479e-3, WithinRel( chunk.covariances().value()(4,6) ) );
        CHECK_THAT( 1.927034e-3, WithinRel( chunk.covariances().value()(4,7) ) );
        CHECK_THAT( 1.882109e-3, WithinRel( chunk.covariances().value()(4,8) ) );
        CHECK_THAT( 1.864828e-3, WithinRel( chunk.covariances().value()(4,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,1) ) );
        CHECK_THAT( 2.173942e-3, WithinRel( chunk.covariances().value()(5,2) ) );
        CHECK_THAT( 2.140176e-3, WithinRel( chunk.covariances().value()(5,3) ) );
        CHECK_THAT( 2.112649e-3, WithinRel( chunk.covariances().value()(5,4) ) );
        CHECK_THAT( 2.123149e-3, WithinRel( chunk.covariances().value()(5,5) ) );
        CHECK_THAT( 2.130883e-3, WithinRel( chunk.covariances().value()(5,6) ) );
        CHECK_THAT( 2.131577e-3, WithinRel( chunk.covariances().value()(5,7) ) );
        CHECK_THAT( 2.150402e-3, WithinRel( chunk.covariances().value()(5,8) ) );
        CHECK_THAT( 2.176944e-3, WithinRel( chunk.covariances().value()(5,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,1) ) );
        CHECK_THAT( 1.843332e-3, WithinRel( chunk.covariances().value()(6,2) ) );
        CHECK_THAT( 1.913301e-3, WithinRel( chunk.covariances().value()(6,3) ) );
        CHECK_THAT( 2.011479e-3, WithinRel( chunk.covariances().value()(6,4) ) );
        CHECK_THAT( 2.130883e-3, WithinRel( chunk.covariances().value()(6,5) ) );
        CHECK_THAT( 2.223439e-3, WithinRel( chunk.covariances().value()(6,6) ) );
        CHECK_THAT( 2.291726e-3, WithinRel( chunk.covariances().value()(6,7) ) );
        CHECK_THAT( 2.362609e-3, WithinRel( chunk.covariances().value()(6,8) ) );
        CHECK_THAT( 2.426673e-3, WithinRel( chunk.covariances().value()(6,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,1) ) );
        CHECK_THAT( 1.579267e-3, WithinRel( chunk.covariances().value()(7,2) ) );
        CHECK_THAT( 1.731503e-3, WithinRel( chunk.covariances().value()(7,3) ) );
        CHECK_THAT( 1.927034e-3, WithinRel( chunk.covariances().value()(7,4) ) );
        CHECK_THAT( 2.131577e-3, WithinRel( chunk.covariances().value()(7,5) ) );
        CHECK_THAT( 2.291726e-3, WithinRel( chunk.covariances().value()(7,6) ) );
        CHECK_THAT( 2.415636e-3, WithinRel( chunk.covariances().value()(7,7) ) );
        CHECK_THAT( 2.531881e-3, WithinRel( chunk.covariances().value()(7,8) ) );
        CHECK_THAT( 2.632081e-3, WithinRel( chunk.covariances().value()(7,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(8,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(8,1) ) );
        CHECK_THAT( 1.391836e-3, WithinRel( chunk.covariances().value()(8,2) ) );
        CHECK_THAT( 1.615025e-3, WithinRel( chunk.covariances().value()(8,3) ) );
        CHECK_THAT( 1.882109e-3, WithinRel( chunk.covariances().value()(8,4) ) );
        CHECK_THAT( 2.150402e-3, WithinRel( chunk.covariances().value()(8,5) ) );
        CHECK_THAT( 2.362609e-3, WithinRel( chunk.covariances().value()(8,6) ) );
        CHECK_THAT( 2.531881e-3, WithinRel( chunk.covariances().value()(8,7) ) );
        CHECK_THAT( 2.689968e-3, WithinRel( chunk.covariances().value()(8,8) ) );
        CHECK_THAT( 2.830254e-3, WithinRel( chunk.covariances().value()(8,9) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(9,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(9,1) ) );
        CHECK_THAT( 1.269227e-3, WithinRel( chunk.covariances().value()(9,2) ) );
        CHECK_THAT( 1.549830e-3, WithinRel( chunk.covariances().value()(9,3) ) );
        CHECK_THAT( 1.864828e-3, WithinRel( chunk.covariances().value()(9,4) ) );
        CHECK_THAT( 2.176944e-3, WithinRel( chunk.covariances().value()(9,5) ) );
        CHECK_THAT( 2.426673e-3, WithinRel( chunk.covariances().value()(9,6) ) );
        CHECK_THAT( 2.632081e-3, WithinRel( chunk.covariances().value()(9,7) ) );
        CHECK_THAT( 3.018361e-3, WithinRel( chunk.covariances().value()(9,9) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          1          5         66         11223133 16     \n"
    " 1.000000-5 1.187260+7 1.200000+7 1.300000+7 1.400000+7 1.500000+7223133 16     \n"
    " 1.600000+7 1.700000+7 1.800000+7 1.900000+7 2.000000+7 0.000000+0223133 16     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0223133 16     \n"
    " 0.000000+0 0.000000+0 0.000000+0 2.500000-1 0.000000+0 0.000000+0223133 16     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0223133 16     \n"
    " 3.897788-3 3.151794-3 2.605989-3 2.173942-3 1.843332-3 1.579267-3223133 16     \n"
    " 1.391836-3 1.269227-3 2.822801-3 2.436598-3 2.140176-3 1.913301-3223133 16     \n"
    " 1.731503-3 1.615025-3 1.549830-3 2.244027-3 2.112649-3 2.011479-3223133 16     \n"
    " 1.927034-3 1.882109-3 1.864828-3 2.123149-3 2.130883-3 2.131577-3223133 16     \n"
    " 2.150402-3 2.176944-3 2.223439-3 2.291726-3 2.362609-3 2.426673-3223133 16     \n"
    " 2.415636-3 2.531881-3 2.632081-3 2.689968-3 2.830254-3 3.018361-3223133 16     \n";
}
