#include <vector>

#include "../catch.hpp"
#include "dvfw/dvfw.hpp"

using namespace dvfw;
const std::string prefix = "[CHUNKS]: ";
/*
TEST_CASE(prefix + "chunking works") {
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<std::vector<int>>{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    std::vector<std::vector<int>> res = {};

    input 
    >>= pipe::chunks<int>(2) 
    >>= sink::push_back(res);

    REQUIRE(res == expected);
}

TEST_CASE(prefix + "chunking chunks works") {
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<std::vector<std::vector<int>>>{{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    std::vector<std::vector<std::vector<int>>> res = {};

    input 
    >>= pipe::chunks<int>(2) 
    >>= pipe::chunks<std::vector<int>>(2) 
    >>= sink::push_back(res);

    REQUIRE(res == expected);
}
*/