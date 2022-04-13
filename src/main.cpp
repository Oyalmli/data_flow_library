#include "dvfw/dvfw.hpp"
#include <iostream>

using namespace dvfw;

int main() {
    auto erroneous_sine_gen = 
        gen::random_err(0.1, 0.0,
        gen::take      (100, 
        gen::sine      (0.01, 10.0, 5.0)));//T freq, T ampl, T yOffset

    erroneous_sine_gen >>= sink::printf("%f\n");
}
