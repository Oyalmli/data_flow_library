#include "dfl/dfl.hpp"
#include <thread>
#include <chrono>

using namespace dfl;
using namespace std::chrono_literals;

int main () {
    auto range_gen = gen::range(10);

    range_gen
    >>= pipe::side_effect([](){ std::this_thread::sleep_for(500ms); })
    >>= sink::print('\n');
}