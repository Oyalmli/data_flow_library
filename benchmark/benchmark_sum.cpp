#include <benchmark/benchmark.h>

#include <iostream>
#include <numeric>

#include "dfl/dfl.hpp"

using namespace dfl;

static void CONST_RANGE_ACCUMULATE(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(1000000LL);
    int64_t sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL,
                                    [](auto acc, auto i) { return acc + i; });
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_ACCUMULATE);

static void CONST_RANGE_REDUCE(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(1000000LL);
    int64_t sum = std::reduce(range_gen.begin(), range_gen.end(), 0LL,
                                [](auto acc, auto i) { return acc + i; });
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_REDUCE);

static void CONST_RANGE_SET_STATE(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range = pipe::set_state([](auto i, auto _sum) { return _sum + i; },
                                     sum) >>= sink::hole();
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_SET_STATE);

static void CONST_RANGE_FOR_EACH(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range = sink::for_each([&sum](auto i) { sum += i; });
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_FOR_EACH);

static void CONST_RANGE_SUM(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range = sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_SUM);

static void CONST_FORLOOP_SUM(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
      sum += i;
    }
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_FORLOOP_SUM);

static void VAR_RANGE_ACCUMULATE(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(state.range(0));
    int64_t sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL,
                                    [](auto acc, auto i) { return acc + i; });
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_RANGE_ACCUMULATE)->Arg(1000000LL);

static void VAR_RANGE_SET_STATE(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range = pipe::set_state([](auto i, auto _sum) { return _sum + i; },
                                     sum) >>= sink::hole();
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_RANGE_SET_STATE)->Arg(1000000LL);

static void VAR_RANGE_FOR_EACH(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range = sink::for_each([&sum](auto i) { sum += i; });
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_RANGE_FOR_EACH)->Arg(1000000LL);

static void VAR_RANGE_SUM(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range = sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_RANGE_SUM)->Arg(1000000LL);

static void VAR_FORLOOP_SUM(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < state.range(0); ++i) {
      sum += i;
    }
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_FORLOOP_SUM)->Arg(1000000LL);

static void VAR_FORLOOP_VOLATILE_SUM(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < state.range(0); ++i) {
      benchmark::DoNotOptimize(sum += i);
    }
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_FORLOOP_VOLATILE_SUM)->Arg(1000000LL);

BENCHMARK_MAIN();