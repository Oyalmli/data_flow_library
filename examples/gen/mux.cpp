#include "dfl/dfl.hpp"
#include <vector>

using namespace dfl;

int main (){
    std::vector<int> nums = {1,5,2,7,4,2};
    auto counter = gen::counter<int>();

    gen:mux(counter, nums) 
    >>= sink::printf("[%d]: %d\n");
}