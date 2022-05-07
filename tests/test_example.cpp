#include "catch.hpp"
const std::string prefix = "[TEST EXAMPLE]: ";

TEST_CASE(prefix + "Testing boolean operators") {
    SECTION("AND") {
        REQUIRE((false && false) == false);
        REQUIRE((false && true) == false);
        REQUIRE((true && false) == false);
        REQUIRE((true && true) == true);
    }
    SECTION("OR") {
        REQUIRE((false || false) == false);
        REQUIRE((false || true) == true);
        REQUIRE((true || false) == true);
        REQUIRE((true || true) == true);
    }
}