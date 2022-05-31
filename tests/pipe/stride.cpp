#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[STRIDE]: ";

TEST_CASE(prefix + "A stride of 1 takes every value")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::stride(1)
          >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}

TEST_CASE(prefix + "A stride of 3 takes every third value, including the first")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1,4,7,10};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::stride(3)
          >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}
