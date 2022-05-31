#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;
int main (){
  int64_t sum = 0;
  auto range_gen = gen::range(1, 1618033988, 3);
  range_gen >>= sink::sum(sum);
  std::cout << sum << '\n';
}