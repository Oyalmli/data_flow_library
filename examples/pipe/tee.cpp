#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main () {
    auto range_gen = gen::range(100);

    range_gen
    >>= pipe::tee(
      pipe::transform([](auto i){ return i*2; }) 
      >>= sink::printf("tee: %d\n"))
    >>= sink::printf("end: %d\n");
}