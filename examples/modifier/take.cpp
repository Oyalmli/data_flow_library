#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main (){
    auto gen42
    =   mod::take(42,
        gen::range(1, 100));

    gen42
    >>= sink::print('\n');

    std::cout << "\n\n";
    for (auto i : mod::take(15, gen::value(10))) {
        std::cout << i << '\n';
    }
}