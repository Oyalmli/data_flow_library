#include <vector>

#include "../catch.hpp"
#include "dfl/dfl.hpp"

using namespace dfl;
const std::string prefix = "[MOVING AVG]: ";

TEST_CASE(prefix + "moving average is returned") {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<double> expected = {1,1.5,2.0,2.5,3.5,4.5,5.5,6.5,7.5,8.5};
    std::vector<double> results;

    numbers 
    >>= pipe::moving_avg<int, 4>()
    >>= sink::push_back(results);

    REQUIRE(results == expected);
}