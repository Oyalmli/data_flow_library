#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
using namespace dfl;
const std::string prefix = "[PRINTF]: ";

TEST_CASE(prefix + "printf compiles")
{
    auto const input = std::vector<int>{};
    input >>= sink::printf("\n");

    REQUIRE(true);
}
