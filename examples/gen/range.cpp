#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main (){
    for (int i : gen::range(1,20,3)) {
        std::cout << i << '\n';
    }
    std::cout << "\n--------------\n\n";
    auto range = gen::range(1,20,3); 
    range >>= sink::print('\n');
}