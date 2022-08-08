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
    >>= pipe::set_state([](auto c, auto ha) { return ((ha << 5) + ha) ^ c; }, hashAddress) 
    >>= sink::hole();
    return hashAddress; })
  >>= sink::print('\n');
}

/* input.txt
a long
list of text 
with many words
*/

/* ./set_state < input.txt
177604
2087658575
2087656743
5861228
2087956376
2088203751
2087696638
191452152
*/