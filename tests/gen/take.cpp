#include <string>
#include <vector>

#include "../catch.hpp"
#include "dvfw/dvfw.hpp"

using namespace dvfw;

const std::string prefix = "[TAKE]: ";

TEST_CASE(prefix + "able to take part of range") {
    auto file_gen = gen::take(5, gen::range<int>(10));

    std::vector<int> expected = {0,1,2,3,4};
    std::vector<int> res = {};

    file_gen >>= sink::push_back(res);

    REQUIRE(res == expected);
}
