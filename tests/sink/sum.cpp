#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[SUM]: ";

TEST_CASE(prefix + "Adds the value to ")
{   
    int sum = 0;
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    input >>= sink::sum(sum);

    REQUIRE(sum == 55);
}
