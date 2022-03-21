#include <vector>

#include "../catch.hpp"
#include "dvfw/generator/file.hpp"


const std::string prefix = "[FILE]: ";

TEST_CASE(prefix + "able to read from file") {
    FILE* pFile = fopen("/Users/oyvind/master/data_validation_framework/tests/generators/inp.txt", "r"); //TODO: fix relative path
    auto file_gen = dvfw::gen::file<int>(pFile);
    
    std::vector<int> expected = {1,-2,3,-4,5};
    std::vector<int> res = {};

    file_gen >>= dvfw::push_back(res);
    
    REQUIRE(res == expected);
    fclose (pFile);
}