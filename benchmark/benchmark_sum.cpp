#include <benchmark/benchmark.h>
#include <numeric>
#include <iostream>
#include "dfl/dfl.hpp"

using namespace dfl;

template <typename T>
class sum_pipeline : public pipeline_base<sum_pipeline<T>> {
   public:
    template<typename V>
    void onReceive(V&& value) {
        benchmark::DoNotOptimize(_acc += (value%13));
    }

    explicit sum_pipeline(T val) : _acc(val) {}

   private:
    T _acc;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
*/
template <typename T>
sum_pipeline<T> sum_mod(T&& val) {
    return sum_pipeline<T>{val};
}

static void CONST_RANGE_Accumulate(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(1000000LL);
    long long sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL, [](auto acc, auto i){
      long long temp;
      benchmark::DoNotOptimize(temp = acc + i%13);
      return temp;
    });
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_RANGE_Accumulate);

static void CONST_RANGE_Reduce(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(1000000LL);
    long long sum = std::reduce(range_gen.begin(), range_gen.end(), 0LL, [](auto acc, auto i){
      long long temp;
      benchmark::DoNotOptimize(temp = acc + i%13);
      return temp;
    });
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_RANGE_Reduce);

static void CONST_RANGE_Set_State(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range
    =   pipe::set_state([](auto i, auto& _sum){
     benchmark::DoNotOptimize(_sum += i%13); }, sum)
    >>= sink::hole();
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_RANGE_Set_State);

static void CONST_RANGE_For_Each(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range
    =   sink::for_each([&sum](auto i){ 
      benchmark::DoNotOptimize(sum += i%13); });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_RANGE_For_Each);

static void CONST_RANGE_sum(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range
    =   sum_mod(sum);
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_RANGE_sum);

static void CONST_FORLOOP_sum(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    for (long long i = 0; i < 1000000LL; ++i) {
      benchmark::DoNotOptimize(sum += i%13);
    }
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_FORLOOP_sum);

static void VAR_RANGE_Accumulate(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(state.range(0));
    long long sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL, [](auto acc, auto i){
      long long temp;
      benchmark::DoNotOptimize(temp = acc + i%13);
      return temp;
    });
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_RANGE_Accumulate)->Arg(1000000LL);

static void VAR_RANGE_Set_State(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range
    =   pipe::set_state([](auto i, auto& _sum){ 
      benchmark::DoNotOptimize(_sum += i%13); }, sum)
    >>= sink::hole();
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_RANGE_Set_State)->Arg(1000000LL);

static void VAR_RANGE_For_Each(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range
    =   sink::for_each([&sum](auto i){ benchmark::DoNotOptimize(sum += i%13); });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_RANGE_For_Each)->Arg(1000000LL);

static void VAR_RANGE_sum(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range
    =   sum_mod(sum);
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_RANGE_sum)->Arg(1000000LL);

static void VAR_FORLOOP_sum(benchmark::State& state) {
  for (auto _ : state) {
    long long sum = 0;
    for (long long i = 0; i < state.range(0); ++i) {
      benchmark::DoNotOptimize(sum += i%13);;
    }
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_FORLOOP_sum)->Arg(1000000LL);

BENCHMARK_MAIN();