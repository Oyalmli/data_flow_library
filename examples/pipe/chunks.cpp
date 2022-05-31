#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto range_gen = gen::range(100);
    range_gen 
    >>= pipe::chunks<int, 10>()
    >>= sink::for_each([](auto vec){ 
        for (auto& i : vec){
            printf("%2d ", i);
        } printf("\n");
    });
}