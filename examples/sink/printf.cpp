#include "dfl/dfl.hpp"

using namespace dfl;
int main (){
    auto noisy_gen 
    = mod::take(100, 
      mod::noise(10, 
      gen::value(10)));
    auto counter = gen::counter<int>();
    gen::mux(counter, noisy_gen) 
    >>= sink::printf("[%2d]: %d\n");
}