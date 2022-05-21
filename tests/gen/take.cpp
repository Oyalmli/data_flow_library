#include <string>
#include <vector>

#include "../catch.hpp"
#include "dfl/dfl.hpp"

using namespace dfl;

const std::string prefix = "[TAKE]: ";

TEST_CASE(prefix + "able to take part of range") {
    auto file_gen = mod::take(5, gen::range<int>(10));

    std::vector<int> expected = {0,1,2,3,4};
    std::vector<int> res = {};

    file_gen >>= sink::push_back(res);

    REQUIRE(res == expected);
}
