#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto noisy_range_gen 
    =   mod::noise(3,
        gen::range(100));

    noisy_range_gen 
    >>= sink::print<'\n'>(); 
}

/*
0
3
0
3
6
4
6
6
10
9
9
9
13
11
14
16
14
17
20
20
*/