#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[FOR_EACH]: ";

TEST_CASE(prefix + "Does function for every recieved value")
{   
    int last_val = 0;
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    input >>= sink::for_each([&last_val](auto i){ last_val = i; });

    REQUIRE(last_val == 10);
}
