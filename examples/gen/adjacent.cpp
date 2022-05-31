#include "dfl/dfl.hpp"
#include <vector>
#include <iostream>

using namespace dfl;

int main (){
    std::vector<int> nums = {1,-10,7,9,-16,4};
    std::vector<int> difs;

    gen::adjacent(nums) 
    >>= pipe::transform([](auto a, auto b) { return a > b ? a - b : b - a; })
    >>= sink::push_back(difs);

    for (auto& i : difs) {
        std::cout << i << '\n';
    }
}

/* ./adjacent
11
17
2
25
20
*/