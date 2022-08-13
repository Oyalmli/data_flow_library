#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
#include <unordered_map>
using namespace dfl;
const std::string prefix = "[HISTOGRAM]: ";

TEST_CASE(prefix + "Creates histogram")
{   
    std::unordered_map<int, int> histogram;
    auto const input = std::vector<int>{1, 1, 2, 2, 3,4};
    input >>= sink::histogram(histogram);

    REQUIRE(histogram[0] == 0);
    REQUIRE(histogram[1] == 2);
    REQUIRE(histogram[2] == 2);
    REQUIRE(histogram[3] == 1);
    REQUIRE(histogram[4] == 1);
    REQUIRE(histogram[5] == 0);
}
