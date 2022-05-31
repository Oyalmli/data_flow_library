#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;
int main (){
    auto noisy_gen = gen::range(10000000);
    noisy_gen
    >>= pipe::transform([](auto i){ return std::to_string(i) + "\n"; })
    >>= sink::to_out_stream(std::cout);
}