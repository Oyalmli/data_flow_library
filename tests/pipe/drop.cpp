#include "../catch.hpp"
#include "dvfw/dvfw.hpp"

#include <vector>
using namespace dvfw;
const std::string prefix = "[DROP]: ";

TEST_CASE(prefix + "drop the first N elements coming from a range")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{3, 4, 5, 6, 7, 8, 9, 10};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::drop(2)
          >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}

TEST_CASE(prefix + "dropping nothing returns full list")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::drop(0)
          >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}

TEST_CASE(prefix + "dropping more than the full list returns empty list")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::drop(11)
          >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}