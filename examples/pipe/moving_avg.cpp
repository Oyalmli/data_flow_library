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

/* ./moving avg
0
1
1
2
2
3
4
6
6
7
8
9
10
12
13
13
14
15
16
17
*/