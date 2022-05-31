#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[ADJACENT]: ";

TEST_CASE(prefix + "the sum of differences between equal elements")
{
    int sum = 0;
    auto input = std::vector<int>{1,1,1,1,1,1,1};

    gen::adjacent(input)
    >>= pipe::transform([](auto i, auto j){ return i - j; })
    >>= sink::sum(sum);
    
    REQUIRE(sum == 0);
}

TEST_CASE(prefix + "the difference between each element in a range is one")
{
    auto input = gen::range(9);
    std::vector<int> expected = {1,1,1,1,1,1,1,1};
    std::vector<int> res;
    gen::adjacent(input)
    >>= pipe::transform([](auto i, auto j){ return j-i;})
    >>= sink::push_back(res);
    
    REQUIRE(res == expected);
}
