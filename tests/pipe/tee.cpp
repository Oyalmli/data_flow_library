#include <vector>

#include "../catch.hpp"
#include "dvfw/dvfw.hpp"
using namespace dvfw;
const std::string prefix = "[TEE]: ";

TEST_CASE(prefix + "splits values to two pipes") {
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected_branch = std::vector<int>{1, 3, 5, 7, 9};
    auto const expected_main = std::vector<int>{2, 4, 6, 8, 10};
    std::vector<int> branch;
    std::vector<int> main;

    input 
    >>= pipe::tee(
        pipe::filter([](int i) { return i % 2 != 0; })
        >>= sink::push_back(branch) ) 
    >>= pipe::filter([](int i) { return i % 2 == 0; }) 
    >>= sink::push_back(main);

    REQUIRE(main == expected_main);
    REQUIRE(branch == expected_branch);
}
