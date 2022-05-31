#include "dfl/dfl.hpp"
#include <iostream>
using namespace dfl;

bool even(int x){
    return x%2 == 0;
}

int main (){
    auto range_gen = gen::range(50);
    std::vector<int> evens;
    std::vector<int> odds;

    range_gen
    >>= pipe::partition(even,
        sink::push_back(evens),
        sink::push_back(odds)
    );
    std::cout << "Even: \n";
    evens >>= sink::print(' ');
    std::cout << "\nOdd: \n";
    odds  >>= sink::print(' ');
    std::cout << '\n';
}