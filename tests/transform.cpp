#include <memory>
#include <vector>

#include "catch.hpp"
#include "dvfw/dvfw.hpp"

const std::string prefix = "[TRANSFORM]: ";

TEST_CASE(prefix + "transforming a vector of ints") {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected = {2, 4, 6, 8, 10};
    std::vector<int> result;

    SECTION("input from range") {
        input 
        >>= dvfw::transform([](int i) { return i * 2; }) 
        >>= dvfw::push_back(result);
        REQUIRE(result == expected);
    }

    SECTION("input from STL algorithm") {
        std::copy(begin(input), end(input), dvfw::transform([](int i) { return i * 2; }) >>= dvfw::push_back(result));
        REQUIRE(result == expected);
    }
}