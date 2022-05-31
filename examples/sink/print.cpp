#include "dfl/dfl.hpp"

using namespace dfl;
int main (){
    auto noisy_gen = gen::range(10000000);
    noisy_gen >>= sink::print('\n');
}