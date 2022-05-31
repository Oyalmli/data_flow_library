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

/* ./push_back
elem: 10
elem: 17
elem: 6
elem: 16
elem: 4
elem: 17
elem: 9
elem: 17
elem: 9
elem: 12
elem: 8
elem: 7
elem: 17
elem: 19
elem: 3
elem: 14
elem: 7
elem: 9
elem: 9
elem: 15
*/