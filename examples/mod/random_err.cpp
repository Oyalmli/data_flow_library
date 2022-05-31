#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    //20% chance of error
    auto noisy_range_gen 
    =   mod::random_err(0.2, 1337,
        gen::range(20));

    noisy_range_gen 
    >>= sink::print('\n'); 
}

/* ./random_err
0
1
2
1337
4
5
6
7
1337
9
10
1337
12
13
14
15
1337
17
1337
19
*/