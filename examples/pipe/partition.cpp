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

/* ./partition
Even: 
0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46 48 
Odd: 
1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49
*/