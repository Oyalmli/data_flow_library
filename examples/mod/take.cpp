#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

auto add_value = [](auto i){ return i + 0; };

int main (){
    mod::take(50, gen::range(0,10,1))
    >>= pipe::transform(add_value)
    >>= sink::printf("%d\n");
}

/* ./take
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

10
10
10
10
10
10
10
10
10
10
*/