#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[INTERSPERSE]: ";

TEST_CASE(prefix + "Inserts the given value between incoming values")
{
    auto const input = std::vector<int>{1,1,1};
    auto const expected = std::vector<int>{1,0,1,0,1};
    
    auto result = std::vector<int>{};
    
    input >>= pipe::intersperse(0)
          >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}
