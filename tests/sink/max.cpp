#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[MAX]: ";

TEST_CASE(prefix + "finds the maximum value in a vector")
{   
    int max = INT32_MIN;
    auto const input = std::vector<int>{1,5,1,1,6,1,13,7,84,5,1,7,3,7,2};
    input >>= sink::max(max);

    REQUIRE(max == 84);
}
