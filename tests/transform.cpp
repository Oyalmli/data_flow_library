#include <memory>
#include <vector>

#include "catch.hpp"
#include "dvfw/helpers/FWD.hpp"
#include "dvfw/operator.hpp"
#include "dvfw/push_back.hpp"
#include "dvfw/transform.hpp"

TEST_CASE("transform") {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected = {2, 4, 6, 8, 10};
    std::vector<int> results;

    SECTION("input from range") {
        input 
            >>= dvfw::transform([](int i) { return i * 2; }) 
            >>= dvfw::push_back(results);
        REQUIRE(results == expected);
    }

    SECTION("input from STL algorithm") {
        std::copy(begin(input), end(input), dvfw::transform([](int i) { return i * 2; }) >>= dvfw::push_back(results));
        REQUIRE(results == expected);
    }
}