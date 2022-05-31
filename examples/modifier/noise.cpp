#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto noisy_range_gen 
    =   mod::noise(3,
        gen::range(100));

    noisy_range_gen 
    >>= sink::print('\n'); 
}