#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[TAP]: ";

TEST_CASE(prefix + "Tap can access the value, but not change it")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::tap([](auto i){ i = 0; })
          >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}

TEST_CASE(prefix + "Tap can capture and change other values")
{   
    int last_val = 10;
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    input >>= pipe::tap([&last_val](auto i){ last_val = i; })
          >>= sink::hole();
    
    REQUIRE(last_val == 10);
}
