#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto range_gen = gen::range(100);

    range_gen
    >>= pipe::drop_while([](auto i){ return i < 90; })
    >>= sink::print('\n');
}