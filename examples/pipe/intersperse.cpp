#include "dfl/dfl.hpp"
#include <vector>
#include <iostream>

using namespace dfl;

int main (){
    auto range_gen = gen::range(10);
    std::vector<int> res;

    range_gen 
    >>= pipe::intersperse(0)
    >>= sink::push_back(res);

    res >>= sink::print<' '>();
    std::cout << '\n';
}

/* ./intersperse
0 0 1 0 2 0 3 0 4 0 5 0 6 0 7 0 8 0 9
*/