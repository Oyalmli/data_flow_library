#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
#include <iostream>
using namespace dfl;
const std::string prefix = "[DROP]: ";


TEST_CASE(prefix + "Side effect does not affect incoming values")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5};
    auto const expected = std::vector<int>{1, 2, 3, 4, 5};
    
    input >>= pipe::side_effect([](){ })
          >>= sink::hole();
    
    REQUIRE(input == expected);
}
