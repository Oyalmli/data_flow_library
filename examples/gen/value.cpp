#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;

int main (){
    int64_t sum = 0;

    auto value_gen 
    =   mod::take(100000000, 
        gen::value(1337));

    value_gen 
    >>= sink::sum(sum);

    std::cout << sum << '\n';
}

/* ./value
133700000000
*/