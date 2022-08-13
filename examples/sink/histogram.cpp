#include "dfl/dfl.hpp"
#include <unordered_map>

using namespace dfl;
int main (){
    std::unordered_map<int, int> hist;
    mod::noise(5, 
    mod::take(100,
    gen::value(0)))
    >>= sink::histogram(hist);
}

/*
map of [value, number of times the value occurred]
*/