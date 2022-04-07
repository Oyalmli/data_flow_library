#include "../catch.hpp"
#include "dvfw/dvfw.hpp"

#include <vector>
using namespace dvfw;
const std::string prefix = "[HOLE]: ";

TEST_CASE(prefix + "hole does not change values")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    input >>= sink::hole();

    REQUIRE(input == expected);
}
