#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main () {
    auto range_gen = gen::range(100);

    range_gen
    >>= pipe::transform([](auto i){ return i*2; })
    >>= pipe::transform([](auto i){ return i%14; })
    >>= pipe::transform([](auto i){ return i*19; })
    >>= pipe::transform([](auto i){ return i-15; })
    >>= pipe::transform([](auto i){ return i/3; })
    >>= pipe::transform([](auto i){ return i-1; })
    >>= sink::print('\n');
}