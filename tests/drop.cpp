#include "catch.hpp"
#include "dvfw/dvfw.hpp"

#include <vector>

const std::string prefix = "[DROP]: ";

TEST_CASE(prefix + "drop the first N elements coming from a range")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{3, 4, 5, 6, 7, 8, 9, 10};
    
    auto result = std::vector<int>{};
    
    input >>= dvfw::drop(2)
          >>= dvfw::push_back(result);
    
    REQUIRE(result == expected);
}

TEST_CASE(prefix + "dropping nothing returns full list")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto result = std::vector<int>{};
    
    input >>= dvfw::drop(0)
          >>= dvfw::push_back(result);
    
    REQUIRE(result == expected);
}

TEST_CASE(prefix + "dropping more than the full list returns empty list")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{};
    
    auto result = std::vector<int>{};
    
    input >>= dvfw::drop(11)
          >>= dvfw::push_back(result);
    
    REQUIRE(result == expected);
}