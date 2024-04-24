// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "codex/format/endf/CovariancePairs.hpp"

// other includes

// convenience typedefs
using namespace njoy::codex;
using namespace njoy::ENDFtk;
using CovariancePairs = section::CovariancePairs;

std::string chunk();

SCENARIO( "CovariancePairs" ) {


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
