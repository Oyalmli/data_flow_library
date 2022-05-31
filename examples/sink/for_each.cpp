#include "dfl/dfl.hpp"

using namespace dfl;
int main (){
    auto generator = gen::range(0, 10);
    auto pipeline 
    =   pipe::transform([](auto i){ return i*2; })
    >>= sink::for_each([](auto i){ printf("%d\n", i); });
    generator >>= pipeline;
}