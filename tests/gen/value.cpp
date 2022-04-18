#include <string>
#include <vector>

#include "../catch.hpp"
#include "dvfw/dvfw.hpp"

using namespace dvfw;

const std::string prefix = "[VALUE]: ";

TEST_CASE(prefix + "able to set number of values wanted") {
    auto file_gen = gen::take(3, gen::value<int>(5));

    std::vector<int> expected = {5,5,5};
    std::vector<int> res = {};

    file_gen >>= sink::push_back(res);

    REQUIRE(res == expected);
}
