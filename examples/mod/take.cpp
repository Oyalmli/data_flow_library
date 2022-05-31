#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main (){
    auto gen42
    =   mod::take(10,
        gen::range(1, 100));

    gen42 >>= sink::print('\n');

    std::cout << "\n";

    for (auto i : mod::take(10, gen::value(10))) {
        std::cout << i << '\n';
    }
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