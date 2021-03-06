#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[MUX]: ";

/*
TEST_CASE(prefix + "the sum of differences between equal elements")
{
    std::vector<int> expected = {1,2,3,4,5};
    std::vector<int> res;
    auto range = gen::range(1,10,2);
    auto count = mod::take(5, gen::counter<int>());

    auto mux = gen::mux(range, count);

    mux 
    >>= pipe::transform([](auto i, auto j){ return i-j; })
    >>= sink::push_back(res);
    REQUIRE(res == expected);
}
*/

TEST_CASE(prefix + "the sum of differences between equal elements")
{
    std::vector<int> expected = {0,0,0,0};
    std::vector<int> vec1 = {1,2,3,4};
    std::vector<int> vec2 = {1,2,3,4};
    auto range = gen::range(1,5);
    std::vector<int> res;
    auto mux = gen::mux(vec1, range);

    mux
    >>= pipe::transform([](auto i, auto j){ return i-j; })
    >>= sink::push_back(res);
    REQUIRE(res == expected);
}

