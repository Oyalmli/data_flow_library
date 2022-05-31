#include "dfl/dfl.hpp"

using namespace dfl;
int main (){
    auto noisy_gen 
    = mod::take(20, 
      mod::noise(10, 
      gen::value(10)));
    auto counter = gen::counter<int>();
    gen::mux(counter, noisy_gen) 
    >>= sink::printf("[%2d]: %d\n");
}

/* ./printf
[ 0]: 10
[ 1]: 17
[ 2]: 12
[ 3]: 7
[ 4]: 10
[ 5]: 19
[ 6]: 1
[ 7]: 17
[ 8]: 5
[ 9]: 8
[10]: 5
[11]: 16
[12]: 10
[13]: 6
[14]: 12
[15]: 9
[16]: 10
[17]: 11
[18]: 2
[19]: 6
*/