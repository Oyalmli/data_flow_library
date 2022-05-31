#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main () {
    auto range_gen = gen::range(20);

    range_gen
    >>= pipe::tap([](auto i){ std::cout << i << '\n'; })
    >>= sink::hole();
}

/* ./tap
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
*/