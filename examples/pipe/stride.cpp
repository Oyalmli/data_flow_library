#include "dfl/dfl.hpp"

using namespace dfl;

int main () {
    auto range_gen = gen::range(100);

    range_gen
    >>= pipe::stride(5)
    >>= sink::print('\n');
}