#include <iostream>
#include <string>

#include "dfl/dfl.hpp"
using namespace dfl;

//Bernstein hash djb2
int main() {
  auto word_gen = gen::file<std::string>(stdin);

  word_gen 
  >>= pipe::transform([](auto str){
    uint32_t hashAddress = 5381;
    str 
    >>= pipe::set_state([](auto c, auto& ha) { ha = ((ha << 5) + ha) ^ c; }, hashAddress) 
    >>= sink::hole();
    return hashAddress; })
  >>= sink::print('\n');
}