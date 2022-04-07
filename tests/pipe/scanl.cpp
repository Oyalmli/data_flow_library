#include <memory>
#include <vector>

#include "../catch.hpp"
#include "dvfw/dvfw.hpp"
using namespace dvfw;
const std::string prefix = "[SCANL]: ";

TEST_CASE(prefix + "scanl with sum") {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 3, 6, 10, 15};
    std::vector<int> result = {};

    input 
    >>= pipe::scanl([](int& acc, int i) { return i + acc; }, 0) 
    >>= sink::push_back(result);

    REQUIRE(result == expected);
}

/* TODO: Implement scanl for string
TEST_CASE(prefix + "scanl with string") {
    std::vector<std::string> input = {"a", "b", "c", "d", "e"};
    std::vector<std::string> expected = {"a","ab","abc","abcd","abcde"};
    std::vector<std::string> result = {};

    input
    >>= dvfw::scanl([](std::string& acc, std::string i){ return acc + i; }, std::string(""))
    >>= dvfw::push_back(result);

    REQUIRE(result == expected);
}
*/