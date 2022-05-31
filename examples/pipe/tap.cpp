#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main () {
    auto range_gen = gen::range(100);

    range_gen
    >>= pipe::tap([](auto i){ std::cout << i << '\n'; })
    >>= sink::hole();
}