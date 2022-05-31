#include "dfl/dfl.hpp"
#include <iostream>

using namespace dfl;
int main (){
  int64_t sum = 0;
  auto range_gen = gen::range(1, 1618033988, 3);
  range_gen >>= sink::sum(sum);
  std::cout << sum << '\n';
}

/* time ./sum
436338997990203022
./sum 0.00s user 0.00s system 1% cpu 0.004 total
*/