#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[PARTITION]: ";

TEST_CASE(prefix + "Sends the incoming values into the the first pipeline if true, the second if false")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1,3,5,7,9};
    
    auto result = std::vector<int>{};
    input
    >>= pipe::partition([](auto i){ return (i&1) == 1; },
            sink::push_back(result),
            sink::hole()
        );
    
    REQUIRE(result == expected);
}
