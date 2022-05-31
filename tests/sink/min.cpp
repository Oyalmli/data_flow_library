#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[MIN]: ";

TEST_CASE(prefix + "finds the minimum value in a vector")
{   
    int min = INT32_MAX;
    auto const input = std::vector<int>{1,5,1,1,6,0,13,7,84,5,1,7,3,7,2};
    input >>= sink::min(min);

    REQUIRE(min == 0);
}
