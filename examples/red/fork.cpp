#include "dfl/dfl.hpp"
#include <vector>
#include <iostream>

using namespace dfl;

int main (){
    std::vector<int> nums = {5,1,7,3,7,1,37,81};
    std::vector<int> res;

    nums 
    >>= red::fork(
        sink::push_back(res),
        pipe::transform([](auto i){ return i/2; }) 
        >>= sink::push_back(res)
    );

    res >>= sink::print<' '>();
    std::cout << '\n';
}

/* ./fork
5 2 1 0 7 3 3 1 7 3 1 0 37 18 81 40 
*/