#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[PRINT]: ";

TEST_CASE(prefix + "print compiles")
{
    auto const input = std::vector<int>{};
    input >>= sink::print();

    REQUIRE(true);
}
