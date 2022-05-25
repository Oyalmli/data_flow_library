#include "dfl/dfl.hpp"
#include <iostream>
#include <iterator>
#include <chrono>

using namespace dfl;
int main(){
    auto range_gen = gen::range(10000000);
    range_gen >>= sink::print('\n');
}
