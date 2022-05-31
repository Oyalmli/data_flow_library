#include "dfl/dfl.hpp"

using namespace dfl;

int main (){
    auto file_gen = gen::file<int>(stdin);
    file_gen >>= sink::print('\n');
}