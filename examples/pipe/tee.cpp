#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main () {
    auto range_gen = gen::range(10);

    range_gen
    >>= pipe::tee(
      pipe::transform([](auto i){ return i*2; }) 
      >>= sink::printf("tee: %d\n"))
    >>= sink::printf("end: %d\n");
}

/* ./tee
tee: 0
end: 0
tee: 2
end: 1
tee: 4
end: 2
tee: 6
end: 3
tee: 8
end: 4
tee: 10
end: 5
tee: 12
end: 6
tee: 14
end: 7
tee: 16
end: 8
tee: 18
end: 9
*/