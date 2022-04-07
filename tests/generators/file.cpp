#include <vector>
#include <string>

#include "../catch.hpp"
#include "dvfw/dvfw.hpp"


const std::string prefix = "[FILE]: ";

TEST_CASE(prefix + "able to read from file") {
    FILE* pFile = fopen("/Users/oyvind/master/data_validation_framework/tests/generators/inp.txt", "r"); //TODO: fix relative path
    auto file_gen = dvfw::gen::file<int>(pFile);
    
    std::vector<int> expected = {1,-2,3,-4,5};
    std::vector<int> res = {};

    file_gen >>= dvfw::sink::push_back(res);
    
    REQUIRE(res == expected);
    fclose (pFile);
}

TEST_CASE(prefix + "able to read words from from file") {
    FILE* pFile = fopen("/Users/oyvind/master/data_validation_framework/tests/generators/inp.txt", "r"); //TODO: fix relative path
    auto file_gen = dvfw::gen::file<std::string, true>(pFile);
    
    std::vector<std::string> expected = {"1","-2","3","-4","5"};
    std::vector<std::string> res = {};

    file_gen >>= dvfw::sink::push_back(res);
    
    REQUIRE(res == expected);
    fclose (pFile);
}

TEST_CASE(prefix + "able to read lines from from file") {
    FILE* pFile = fopen("/Users/oyvind/master/data_validation_framework/tests/generators/inp.txt", "r"); //TODO: fix relative path
    auto file_gen = dvfw::gen::file<std::string, false>(pFile);
    
    std::vector<std::string> expected = {"1","-2","3 -4","5"};
    std::vector<std::string> res = {};

    file_gen >>= dvfw::sink::push_back(res);
    
    REQUIRE(res == expected);
    fclose (pFile);
}

