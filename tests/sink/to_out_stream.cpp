#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
#include <iostream>
using namespace dfl;
const std::string prefix = "[TO_OUT_STREAM]: ";

TEST_CASE(prefix + "to_out_stream compiles")
{
    auto const input = std::vector<int>{};
    input >>= sink::to_out_stream(std::cout);

    REQUIRE(true);
}
