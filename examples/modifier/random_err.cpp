#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto noisy_range_gen 
    =   mod::random_err(0.2, 1337,
        gen::range(100));

    noisy_range_gen 
    >>= sink::print('\n'); 
}