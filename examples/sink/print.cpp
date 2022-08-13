#include "dfl/dfl.hpp"

using namespace dfl;
int main (){
    gen::range(10000000)
    >>= sink::print<'\n'>();
}

//prints the numbers to stdout
/* time ./print > /dev/null
./print > /dev/null  0.66s user 0.00s system 99% cpu 0.664 total
*/