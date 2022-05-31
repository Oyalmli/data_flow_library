#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto inf_gen
    =   mod::repeat(
        mod::take(5,
        gen::range(100)));

    inf_gen  
    >>= sink::print('\n'); 
}