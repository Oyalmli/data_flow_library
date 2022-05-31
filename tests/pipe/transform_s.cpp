#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[DROP]: ";

TEST_CASE(prefix + "transform_s can change its own state, but not incoming values")
{   
    int last_val = 0;
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const input_copy = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::transform_s([](auto i, auto& state){
        auto temp = i;
        state = temp;
        i = 0;
        return temp + state; 
        }, last_val)
          >>= sink::push_back(result);
    
    REQUIRE(input == input_copy);
    REQUIRE(result == expected);
}
