#include <benchmark/benchmark.h>
#include <fstream>
#include <cstdio>
#include <iostream>

#include "dfl/dfl.hpp"

using namespace dfl;

static void CONST_RANGE_many_ops(benchmark::State& state) {
  for (auto _ : state) {
      int64_t acc = 0, sum = 0;
    auto range_gen = gen::range(1000000LL);
    
    auto transform_pipeline 
    =   pipe::transform([](auto i){ return i%13; })
    >>= pipe::set_state([](auto i, auto& _state){ _state = i + (_state%9); }, acc)
    >>= pipe::transform_s([](auto i, auto& _state){ return i + _state; }, acc);
    
    auto pipeline
    =   transform_pipeline
    >>= pipe::partition([](auto i){ return (i%13) == 0; },
        pipe::transform([](auto i){ return i + 13;})
        >>= sink::sum(sum),
        sink::hole()
    );
    range_gen >>= pipeline;
    assert(sum == 2333344);

  }
}
BENCHMARK(CONST_RANGE_many_ops);

static void CONST_LOOP_many_ops(benchmark::State& state) {
  for (auto _ : state) {
    int64_t acc = 0, sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i){
        int64_t x = (i%13);
        acc = x + (acc % 9);
        x += acc;
        if ((x%13) == 0) {
            x += 13;
            sum += x;
        }
    }
    assert(sum == 2333344);

  }
}
BENCHMARK(CONST_LOOP_many_ops);

BENCHMARK_MAIN();