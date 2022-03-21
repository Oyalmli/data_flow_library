#include "catch.hpp"
#include "dvfw/dvfw.hpp"

#include <vector>

const std::string prefix = "[FILTER]: ";

TEST_CASE(prefix + "filters out odd numbers")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{2, 4, 6, 8, 10};
    std::vector<int> res;
    
    input 
    >>= dvfw::filter([](int i){ return i % 2 == 0; })
    >>= dvfw::push_back(res);

    REQUIRE(res == expected);
}