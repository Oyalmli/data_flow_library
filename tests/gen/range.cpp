#include <string>
#include <vector>

#include "../catch.hpp"
#include "dvfw/dvfw.hpp"

using namespace dvfw;

const std::string prefix = "[RANGE]: ";

TEST_CASE(prefix + "simple positive range") {
    auto range_gen = gen::range<int>(5);

    std::vector<int> expected = {0,1,2,3,4};
    std::vector<int> res = {};

    range_gen >>= sink::push_back(res);

    REQUIRE(res == expected);
}
