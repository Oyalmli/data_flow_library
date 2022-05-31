#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main (){
    // 10 samples period, 1.0 amplitude, 0.0 baseline
    auto sine_gen 
    =   mod::take(20,
        gen::sine(0.1, 1.0, 0.0)); 

    sine_gen >>= sink::printf("% .2f\n");
}

/* ./sine
 0.00
 0.59
 0.95
 0.95
 0.59
 0.00
-0.59
-0.95
-0.95
-0.59
-0.00
 0.59
 0.95
 0.95
 0.59
 0.00
-0.59
-0.95
-0.95
-0.59
*/