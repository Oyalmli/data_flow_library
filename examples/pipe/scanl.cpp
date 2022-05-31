#include "dfl/dfl.hpp"
#include <iostream>
using namespace dfl;

//https://open.kattis.com/problems/overdraft
int main () {
    auto file_gen = gen::file<int64_t>(stdin);

    int64_t min_found = INT64_MAX;
    
    file_gen
    >>= pipe::drop(1)
    >>= pipe::scanl([](auto a, auto b){ return a+b; }, 0LL)
    >>= sink::min(min_found);
    
    std::cout << std::max(0LL, -min_found);
}