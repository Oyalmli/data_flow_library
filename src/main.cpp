#include <iostream>
#include "dvfw/dvfw.hpp"

using namespace dvfw;
int main() {
    auto range_gen = gen::range<int>(10000000);
    range_gen
    >>= pipe::transform([](int i){ return i+1; })
    >>= pipe::partition([](int i){ return (i&1)==0; },
        sink::printf("even: %d\n"),
        sink::printf("odd: %d\n"));
}
