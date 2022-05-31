#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;
int main (){
    int min = INT32_MAX;
    auto noisy_gen = mod::noise(100, gen::value(0));
    
    noisy_gen
    >>= sink::min(min);

    std::cout << min << '\n';
}

/* ./min
-96
*/