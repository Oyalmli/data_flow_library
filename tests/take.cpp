#include "catch.hpp"
#include "dvfw/dvfw.hpp"

#include <vector>

TEST_CASE("take takes the first N elements coming from a range")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1, 2, 3, 4, 5, 6};
    
    auto result = std::vector<int>{};
    
    input >>= dvfw::take(6)
          >>= dvfw::push_back(result);
    
    REQUIRE(result == expected);
}