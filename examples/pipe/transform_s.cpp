#include "dfl/dfl.hpp"

using namespace dfl;

int main () {
    auto noisy_value 
    =   mod::take(100, 
        mod::noise(1000, 
        gen::value(0)));

    int floor = 0;

    noisy_value 
    >>= pipe::set_state([](auto i, auto& floor){ floor = std::max(i, floor); }, floor)
    >>= pipe::transform_s([](auto i, auto& floor){ return i + floor; } , floor)
    >>= sink::print('\n');
}