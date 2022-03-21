#include <vector>

#include "catch.hpp"
#include "dvfw/dvfw.hpp"

const std::string prefix = "[TEE]: ";

TEST_CASE(prefix + "fork dispatches an input to several destinations") {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<int> expected1 = {2, 4, 6, 8, 10};
    std::vector<int> expected2 = {1, 3, 5, 7, 9};
    std::vector<int> expected3 = numbers;

    std::vector<int> results1, results2, results3;

    numbers >>= dvfw::fork(
        dvfw::filter([](int i) { return (i & 1) == 0; }) >>= dvfw::push_back(results1),
        dvfw::filter([](int i) { return (i & 1) == 1; }) >>= dvfw::push_back(results2),
        dvfw::push_back(results3));

    REQUIRE(results1 == expected1);
    REQUIRE(results2 == expected2);
    REQUIRE(results3 == expected3);
}