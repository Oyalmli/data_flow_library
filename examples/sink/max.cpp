#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;
int main (){
    int max = INT32_MIN;
    auto noisy_gen 
    = mod::take(100, 
      mod::noise(100, 
      gen::value(0)));
    
    noisy_gen
    >>= sink::max(max);

    std::cout << max << '\n';
}

/* ./max
99
*/