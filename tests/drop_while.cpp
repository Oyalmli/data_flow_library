#include "catch.hpp"
#include "dvfw/dvfw.hpp"

#include <vector>

const std::string prefix = "[DROP_WHILE]: ";

TEST_CASE(prefix + "dropwhile on numbers")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{6, 7, 8, 9, 10};
    std::vector<int> res = {};

    input 
    >>= dvfw::drop_while([](int i){ return i != 6; }) 
    >>= dvfw::push_back(res);

    REQUIRE(res == expected);
}
