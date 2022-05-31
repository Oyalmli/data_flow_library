#include "dfl/dfl.hpp"
#include <vector>
#include <iostream>

using namespace dfl;
int main (){
  std::vector<int> vec;
  auto noisy_gen 
  = mod::take(100, 
    mod::noise(10, 
    gen::value(10)));

  noisy_gen 
  >>= sink::push_back(vec);

  for (auto& elem : vec) {
    std::cout << "elem: " << elem << '\n';
  }
}