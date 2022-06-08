#include <benchmark/benchmark.h>
#include <iostream>
#include <numeric>
#include "dfl/dfl.hpp"

using namespace dfl;

template <typename T>
class sum_dno : public pipeline_base<sum_dno<T>> {
   public:
    template<typename V>
    void onReceive(V&& value) {
        T temp; 
        benchmark::DoNotOptimize(temp = _acc + value);
        _acc = temp;
    }
    sum_dno(T& val) : _acc(val) {}

   private:
    T& _acc;
};

static void CONST_RANGE_SUM_MOD_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range 
    = sink::for_each([&sum](auto i){ 
            int64_t temp;
            benchmark::DoNotOptimize(temp = i%13);
            sum += temp; 
        });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_RANGE_SUM_MOD_DNO);

static void CONST_RANGE_SUM_MOD(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range 
    = sink::for_each([&sum](auto i){
            int64_t temp;
            temp = (i%13);
            sum += temp;

        });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_RANGE_SUM_MOD);

static void VAR_RANGE_SUM_MOD_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range 
    = sink::for_each([&sum](auto i){ 
            int64_t temp;
            benchmark::DoNotOptimize(temp = i%13);
            sum += temp; 
        });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_RANGE_SUM_MOD_DNO)->Arg(1000000LL);

static void VAR_RANGE_SUM_MOD(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range 
    = sink::for_each([&sum](auto i){
            int64_t temp;
            temp = (i%13);
            sum += temp;

        });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_RANGE_SUM_MOD)->Arg(1000000LL);

////LOOP////
static void CONST_LOOP_SUM_MOD_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
        int64_t temp;
        benchmark::DoNotOptimize(temp = (i%13));
        sum += temp;
    }
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_LOOP_SUM_MOD_DNO);

static void CONST_LOOP_SUM_MOD(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range 
    = sink::for_each([&sum](auto i){
            int64_t temp;
            temp = (i%13);
            sum += temp;

        });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(CONST_LOOP_SUM_MOD);

static void VAR_LOOP_SUM_MOD_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range 
    = sink::for_each([&sum](auto i){ 
            int64_t temp;
            benchmark::DoNotOptimize(temp = (i%13));
            sum += temp; 
        });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_LOOP_SUM_MOD_DNO)->Arg(1000000LL);

static void VAR_LOOP_SUM_MOD(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range 
    = sink::for_each([&sum](auto i){
            int64_t temp;
            temp = (i%13);
            sum += temp;

        });
    range_gen >>= sum_range;
    assert(sum == 5999994);
  }
}
BENCHMARK(VAR_LOOP_SUM_MOD)->Arg(1000000LL);


////////////////////////////////
//            CONST           //
////////////////////////////////
static void CONST_RANGE_SUM_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(1000000LL);
    auto sum_range = sum_dno(sum);
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_SUM_DNO);

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

static void VAR_RANGE_SUM_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto range_gen = gen::range(state.range(0));
    auto sum_range = sum_dno(sum);
    range_gen >>= sum_range;
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_RANGE_SUM_DNO)->Arg(1000000LL);

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

static void CONST_RANGE_ACCUMULATE_DNO(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(1000000LL);
    int64_t sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL, [](auto acc, auto curr){
        benchmark::DoNotOptimize(acc = acc+curr);
        return acc;
    });
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_ACCUMULATE_DNO);

static void CONST_RANGE_ACCUMULATE(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(1000000LL);
    int64_t sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL, [](auto acc, auto curr){
        return acc+curr;
    });
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_RANGE_ACCUMULATE);

static void VAR_RANGE_ACCUMULATE_DNO(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(state.range(0));
    int64_t sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL, [](auto acc, auto curr){
        benchmark::DoNotOptimize(acc = acc+curr);
        return acc;
    });
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_RANGE_ACCUMULATE_DNO)->Arg(1000000LL);

static void VAR_RANGE_ACCUMULATE(benchmark::State& state) {
  for (auto _ : state) {
    auto range_gen = gen::range(state.range(0));
    int64_t sum = std::accumulate(range_gen.begin(), range_gen.end(), 0LL, [](auto acc, auto curr){
        return acc+curr;
    });
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_RANGE_ACCUMULATE)->Arg(1000000LL);

static void CONST_LOOP_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
        benchmark::DoNotOptimize(sum += i);
    }
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_LOOP_DNO);

static void CONST_LOOP(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
        sum += i;
    }
    assert(sum == 499999500000);
  }
}
BENCHMARK(CONST_LOOP)->Arg(1000000LL);

static void VAR_LOOP_DNO(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < state.range(0); ++i) {
        benchmark::DoNotOptimize(sum += i);
    }
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_LOOP_DNO)->Arg(1000000LL);

static void VAR_LOOP(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
        sum += i;
    }
    assert(sum == 499999500000);
  }
}
BENCHMARK(VAR_LOOP)->Arg(1000000LL);

BENCHMARK_MAIN();
