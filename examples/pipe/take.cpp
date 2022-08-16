#include "dfl/dfl.hpp"

using namespace dfl;

int main () {
    auto range_gen = gen::range(100);

    range_gen
    >>= pipe::take(5)
    >>= sink::print<'\n'>();
}

/* ./take
0
1
2
3
4
*/