#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[COUNTER]: ";

TEST_CASE(prefix + "the counter counts from 0")
{   
    std::vector<int> expected = {0,1,2,3,4};
    std::vector<int> res;
    
    auto range = mod::take(5, gen::counter<int>());
    
    range
    >>= sink::push_back(res);
    
    REQUIRE(res == expected);
}
