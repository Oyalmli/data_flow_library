#include <vector>

#include "../catch.hpp"
#include "dfl/dfl.hpp"

using namespace dfl;
const std::string prefix = "[FILTER]: ";

TEST_CASE(prefix + "filters out odd numbers") {
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{2, 4, 6, 8, 10};
    std::vector<int> res;

    input 
    >>= pipe::filter(_even) 
    >>= sink::push_back(res);

    REQUIRE(res == expected);
}
