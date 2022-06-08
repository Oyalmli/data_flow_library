#include <benchmark/benchmark.h>

#include "dfl/dfl.hpp"

using namespace dfl;

template <typename T, size_t MIN, size_t MAX, size_t STEP>
class range2 : public gen::base_generator<range2<T, MIN, MAX, STEP>, T> {
 private:
  T _curr;

 public:
  /**
   * @brief Construct a range generator
   *
   */
  range2() : _curr{0} {};
  using class_type = range2<T, MIN, MAX, STEP>;
  IT(class_type, T);

  bool hasNext() { return _curr < MAX; }

  T next() { return (_curr += STEP); }

  T curr() { return _curr; }
};

static void CONST_Range_plus2_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    int64_t sum = 0;
    auto range_gen = gen::range(0LL, 1000000LL, 2LL);
    auto sum_range = sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000);
  }
}
BENCHMARK(CONST_Range_plus2_skip_half);


static void CONST_Range2_plus2_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    int64_t sum = 0;
    auto range_gen = range2<int64_t, 0LL, 1000000LL, 2LL>();
    auto sum_range = sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000);
  }
}
BENCHMARK(CONST_Range2_plus2_skip_half);

static void CONST_ForLoop_plus2_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    long long sum = 0;
    for (long long i = 0; i < 1000000LL; i+=2) {
      sum += i;
    }
    assert(sum == 249999500000);
  }
}
BENCHMARK(CONST_ForLoop_plus2_skip_half);

BENCHMARK_MAIN();
