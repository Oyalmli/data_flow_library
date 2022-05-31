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

    res >>= sink::print(' ');
    std::cout << '\n';
}