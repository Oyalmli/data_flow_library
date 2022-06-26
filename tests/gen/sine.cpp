#include "../catch.hpp"
#include "dfl/dfl.hpp"

#include <vector>
#include <iostream>
using namespace dfl;
const std::string prefix = "[SINE]: ";

bool compare_double(double x, double y, double epsilon = 0.01){
   return fabs(x - y) < epsilon;
}

TEST_CASE(prefix + "generates a sine function")
{   
    auto all = true;
    auto sine = mod::take(10, gen::sine(0.083333,1.0,0.0));
    std::vector<double> res;
    std::vector<double> expected = 
        {  0.000000,  0.499998,  0.866023,  1.000000,  0.866030
        ,  0.500009,  0.000013, -0.499987, -0.866017, -1.000000};
    gen::mux(sine, expected) >>= sink::for_each([&all](auto s, auto e){
        all &= compare_double(s, e, 0.000001);
    });

    REQUIRE(all);
}
