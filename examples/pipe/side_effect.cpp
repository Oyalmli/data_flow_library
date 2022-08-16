#include "dfl/dfl.hpp"
#include <thread>
#include <chrono>

using namespace dfl;
using namespace std::chrono_literals;

int main () {
    auto range_gen = gen::range(10);

    range_gen
    >>= pipe::side_effect([](){ std::this_thread::sleep_for(500ms); })
    >>= sink::print<'\n'>();
}

//every print is separated by a 500ms wait
/* ./side_effect
0
1
2
3
4
5
6
7
8
9
*/