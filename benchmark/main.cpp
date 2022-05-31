#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;
int main (){
    IO io;
    auto noisy_gen = gen::range(10000000);
    noisy_gen
    >>= pipe::transform([](auto i){ return std::to_string(i) + "\n"; })
    >>= sink::to_out_stream(io);
    io.writer.flush();
}
//prints the numbers to specified out stream
/* time ./to_out_stream > /dev/null
./to_out_stream > /dev/null  0.83s user 0.00s system 99% cpu 0.836 total
*/