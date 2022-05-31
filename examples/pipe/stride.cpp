#include "dfl/dfl.hpp"

using namespace dfl;

int main () {
    auto range_gen = gen::range(20);

    range_gen
    >>= pipe::stride(5)
    >>= sink::print('\n');
}

/* ./stride
0
5
10
15
*/