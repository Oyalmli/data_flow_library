#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    //noisy range with +-2
    auto range_gen = mod::noise(2, gen::range(100));

    //using moving average to smooth out the values
    range_gen 
    >>= pipe::moving_avg<int, 5>()
    >>= sink::printf("%.0f\n");
}