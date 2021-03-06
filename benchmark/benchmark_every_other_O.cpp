#include <benchmark/benchmark.h>

#include "dfl/dfl.hpp"

using namespace dfl;

class bool_cycle : public gen::base_generator<bool_cycle, bool>{
    bool _b{true};
    public:
    MAKE_ITER(bool_cycle, bool);
    bool hasNext(){ return true; }
    bool next() { _b = !_b; return _b; }
    bool curr() { return _b; }
};

////////////////////////////////
//            CONST           //
////////////////////////////////
static void CONST_Range_stride_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range = pipe::stride(2LL) >>= sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_Range_stride_skip_half);

static void CONST_Range_bool_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto bool_gen = bool_cycle();
    auto range_gen = gen::range(1000000LL);
    auto mux_gen = gen::mux(bool_gen, range_gen);
    auto sum_range 
    =   pipe::partition([](auto b, auto i){ return b; },
            pipe::transform([](auto b, auto i){ return i; }) >>= sink::sum(sum),
            sink::hole()
        );
    mux_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_Range_bool_partition_skip_half);

static void CONST_Range_bool_arithmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto bool_gen = bool_cycle();
    auto range_gen = gen::range(1000000LL);
    auto mux_gen = gen::mux(bool_gen, range_gen);
    auto sum_range = pipe::transform([](auto b, auto i){ return (i*b); }) >>= sink::sum(sum);
    mux_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_Range_bool_arithmetic_skip_half);

static void CONST_Range_even_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range = pipe::partition([](auto i) { return ((i & 1) == 0); },
                                     sink::sum(sum), sink::hole());
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_Range_even_partition_skip_half);

static void CONST_Range_even_arithmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range =
        pipe::transform([](auto i) { return i * ((i & 1) == 0); }) >>=
        sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_Range_even_arithmetic_skip_half);

static void CONST_Range_plus2_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    int64_t sum = 0;
    auto range_gen = gen::range(0LL, 1000000LL, 2LL);
    auto sum_range = sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_Range_plus2_skip_half);

static void CONST_ForLoop_stride_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    int64_t stride = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
      if (stride == 0) {
        sum += i;
        stride = 1;
      } else {
        --stride;
      }
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_ForLoop_stride_skip_half);

static void CONST_ForLoop_bool_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    bool skip = false;
    for (int64_t i = 0; i < 1000000LL; ++i) {
      if (skip) {
        skip = false;
      } else {
        sum += i;
        skip = true;
      }
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_ForLoop_bool_partition_skip_half);

static void CONST_ForLoop_bool_artihmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    bool keep = true;
    for (int64_t i = 0; i < 1000000LL; ++i) {
      sum += (i * keep);
      keep = !keep;
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_ForLoop_bool_artihmetic_skip_half);

static void CONST_ForLoop_even_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
      if((i&1)==0){
        sum += i;
      }
      
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_ForLoop_even_partition_skip_half);

static void CONST_ForLoop_even_arithmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
      sum += (((i&1)==0) * i);
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_ForLoop_even_arithmetic_skip_half);

static void CONST_ForLoop_plus2_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; i+=2) {
      sum += i;
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(CONST_ForLoop_plus2_skip_half);

////////////////////////////////
//          VARIABLE          //
////////////////////////////////
static void VAR_Range_stride_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range = pipe::stride(2LL) >>= sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_Range_stride_skip_half)->Arg(1000000LL);

static void VAR_Range_bool_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto bool_gen = bool_cycle();
    auto range_gen = gen::range(state.range(0));
    auto mux_gen = gen::mux(bool_gen, range_gen);
    auto sum_range 
    =   pipe::partition([](auto b, auto i){ return b; },
            pipe::transform([](auto b, auto i){ return i; }) >>= sink::sum(sum),
            sink::hole()
        );
    mux_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_Range_bool_partition_skip_half)->Arg(1000000LL);

static void VAR_Range_bool_arithmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto bool_gen = bool_cycle();
    auto range_gen = gen::range(state.range(0));
    auto mux_gen = gen::mux(bool_gen, range_gen);
    auto sum_range = pipe::transform([](auto b, auto i){ return (i*b); }) >>= sink::sum(sum);
    mux_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_Range_bool_arithmetic_skip_half)->Arg(1000000LL);

static void VAR_Range_even_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range = pipe::partition([](auto i) { return ((i & 1) == 0); },
                                     sink::sum(sum), sink::hole());
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_Range_even_partition_skip_half)->Arg(1000000LL);

static void VAR_Range_even_arithmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range =
        pipe::transform([](auto i) { return i * ((i & 1) == 0); }) >>=
        sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_Range_even_arithmetic_skip_half)->Arg(1000000LL);

static void VAR_Range_plus2_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    int64_t sum = 0;
    auto range_gen = gen::range(0LL, state.range(0), 2LL);
    auto sum_range = sink::sum(sum);
    range_gen >>= sum_range;
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_Range_plus2_skip_half)->Arg(1000000LL);

static void VAR_ForLoop_stride_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    int64_t stride = 0;
    for (int64_t i = 0; i < state.range(0); ++i) {
      if (stride == 0) {
        sum += i;
        stride = 1;
      } else {
        --stride;
      }
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_ForLoop_stride_skip_half)->Arg(1000000LL);

static void VAR_ForLoop_bool_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    bool skip = false;
    for (int64_t i = 0; i < state.range(0); ++i) {
      if (skip) {
        skip = false;
      } else {
        sum += i;
        skip = true;
      }
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_ForLoop_bool_partition_skip_half)->Arg(1000000LL);

static void VAR_ForLoop_bool_artihmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    bool keep = true;
    for (int64_t i = 0; i < state.range(0); ++i) {
      sum += (i * keep);
      keep = !keep;
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_ForLoop_bool_artihmetic_skip_half)->Arg(1000000LL);

static void VAR_ForLoop_even_partition_skip_half(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < state.range(0); ++i) {
      if((i&1)==0){
        sum += i;
      }
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_ForLoop_even_partition_skip_half)->Arg(1000000LL);

static void VAR_ForLoop_even_artihmetic_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    int64_t sum = 0;
    for (int64_t i = 0; i < state.range(0); ++i) {
      sum += (((i&1)==0) * i);
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_ForLoop_even_artihmetic_skip_half)->Arg(1000000LL);

static void VAR_ForLoop_plus2_skip_half(benchmark::State& state) {
  for (auto _ : state) {      
    int64_t sum = 0;
    for (int64_t i = 0; i < state.range(0); i+=2) {
      sum += i;
    }
    assert(sum == 249999500000LL);
  }
}
BENCHMARK(VAR_ForLoop_plus2_skip_half)->Arg(1000000LL);

BENCHMARK_MAIN();
