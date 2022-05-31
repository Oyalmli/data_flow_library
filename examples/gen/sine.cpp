#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main (){
    // 1000 samples period, 1.0 amplitude, 0.0 baseline
    auto sine_gen = gen::sine(0.01, 1.0, 0.0); 

    sine_gen >>= sink::printf("% .2f\n");
}