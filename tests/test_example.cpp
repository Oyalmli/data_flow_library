#include "catch.hpp"
#include <vector>
#include <algorithm>

const std::string prefix = "[TEST EXAMPLE]: ";

TEST_CASE(prefix + "Example test with two sections") {
    SECTION("ONE") {
        REQUIRE(true == true);
    }
    SECTION("TWO") {
        std::vector<int> x = {1,2,3}, y = {3,2,1};
        REQUIRE(x != y);
        std::reverse(y.begin(), y.end());
        REQUIRE(x == y);
    }
}