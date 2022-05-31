#include "dfl/dfl.hpp"
#include <vector>

using namespace dfl;

int main (){
    std::vector<int> nums = {5,1,7,3,7,1,37,81};

    gen::adjacent(nums)
    >>= pipe::filter([](auto a, auto b){ return a < b; })
    >>= pipe::transform([](auto i, auto...){ return i; })
    >>= sink::printf("%d\n");
}