#include <iostream>
#include <numeric>
#include <vector>

#include "dfl/dfl.hpp"

class Mem_measure {
  rusage baseline;
  rusage curr;
  rusage prev;

 public:
  Mem_measure() {}

  Mem_measure& initialize() {
    printf("-- !MEMORY MEASUREMENT START! --\n");
    getrusage(RUSAGE_SELF, &curr);
    prev = curr;
    getrusage(RUSAGE_SELF, &baseline);
    return *this;
  }
  Mem_measure& measure() {
    prev = curr;
    getrusage(RUSAGE_SELF, &curr);
    return *this;
  }

  Mem_measure& print_mem() {
    printf("%ld;%ld;%ld;%ld;\n", baseline.ru_maxrss, curr.ru_maxrss,
           curr.ru_maxrss - baseline.ru_maxrss,
           curr.ru_maxrss - prev.ru_maxrss);
    return *this;
  }
} mm;

using namespace dfl;

int main() {
  mm.initialize();
  mm.measure().print_mem();
  int64_t sum = 0, cnt = 0;
  auto range_gen = gen::range(640'000'000);
  range_gen
  >>= pipe::chunks<int64_t, 5>()
  >>= pipe::side_effect([&cnt](){ if(cnt++ >= 10000000)
  {mm.measure().print_mem(); cnt = 0; } })
  >>= sink::for_each([&sum](auto vec){
        sum += (std::accumulate(vec.begin(), vec.end(),0LL)%13);
        //printf("sum: %lld\n", sum);

      });
  /*std::vector<int64_t> vec(5);
  for (int64_t i = 0; i < 640'000'000; ++i) {
    vec.push_back(i);
    if (vec.size() >= 5 || i == 640'000'000- 1) {
      if (cnt++ >= 10000000) {
        mm.measure().print_mem();
        cnt = 0;
      }
      sum += (std::accumulate(vec.begin(), vec.end(), 0LL) % 13);
      vec.clear();
      //767999989
      //768000002
    }
  }
  */
  mm.measure().print_mem();
  printf("%lld\n", sum);
}
