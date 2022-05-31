#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[PUSH_BACK]: ";

TEST_CASE(prefix + "pushes the values recieved into the container")
{
    auto const input = std::vector<int>{1,2,3};
    std::vector<int> res = {};
    input >>= sink::push_back(res);

    REQUIRE(res == input);
}
