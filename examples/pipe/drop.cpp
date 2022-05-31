#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto range_gen = gen::range(100);

    range_gen
    >>= pipe::drop(90)
    >>= sink::print('\n');
}

/* ./drop
90
91
92
93
94
95
96
97
98
99
*/