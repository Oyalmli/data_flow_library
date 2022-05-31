#include "dfl/dfl.hpp"
#include <vector>
#include <iostream>

using namespace dfl;

int main (){
    std::vector<int> nums = {5,1,7,3,7,1,37,81};
    std::vector<int> res;

    nums 
    >>= pipe::fork(
        sink::push_back(res),
        pipe::transform([](auto i){ return i/2; }) 
        >>= sink::push_back(res)
    );

    res >>= sink::print(' ');
    std::cout << '\n';
}