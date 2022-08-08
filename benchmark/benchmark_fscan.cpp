#include <benchmark/benchmark.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>

#include "dfl/dfl.hpp"

using namespace dfl;

template <typename T>
class file_fstream_gen : public gen::base_generator<T> {
  std::fstream _stream;
  T _curr;

 public:
  file_fstream_gen(const char* path) : _stream{path} { _stream >> _curr; }

  bool hasNext() const { return !_stream.eof(); }
  T curr() const { return _curr; }
  void next() { _stream >> _curr; }

  MAKE_ITER(file_fstream_gen, T);
};

class file_fscanf_gen : public gen::base_generator<int64_t> {
  FILE* _fp;
  int64_t _curr;
  bool _more = true;

 public:
  file_fscanf_gen(const char* path) {
    _fp = fopen(path, "r");
    fscanf(_fp, "%lld", &_curr);
  }
  bool hasNext() const { return _more; }
  int64_t curr() const { return _curr; }
  void next() {
    _more = (fscanf(_fp, "%lld", &_curr) != EOF);
  }
  
  MAKE_ITER(file_fscanf_gen, int64_t);
};

/////////////////////////
//      GENERATORS     //
/////////////////////////
static void GENERATOR_File_read(benchmark::State& state) {
  for (auto _ : state) {
    FILE* fp = fopen("../benchmark/inp.txt", "r");
    int64_t sum = 0;
    auto inp_gen = gen::file<int64_t>(fp);
    auto pipeline = sink::sum(sum);
    inp_gen >>= pipeline;
    assert(sum == 49858177396);
  }
}
BENCHMARK(GENERATOR_File_read);

static void GENERATOR_fstream_File_read(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto inp_gen = file_fstream_gen<int64_t>("../benchmark/inp.txt");
    auto pipeline = sink::sum(sum);
    inp_gen >>= pipeline;
    assert(sum == 49858177396);
  }
}
BENCHMARK(GENERATOR_fstream_File_read);

static void GENERATOR_fscanf_File_read(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto inp_gen = file_fscanf_gen("../benchmark/inp.txt");
    auto pipeline = sink::sum(sum);
    inp_gen >>= pipeline;
    assert(sum == 49858177396);
  }
}
BENCHMARK(GENERATOR_fscanf_File_read);

/////////////////////////
//        LOOPS        //
/////////////////////////
static void LOOP_File_read(benchmark::State& state) {
  for (auto _ : state) {
    FILE* fp = fopen("../benchmark/inp.txt", "r");
    int64_t sum = 0;
    Reader<128> reader(fp);
    while (reader.hasNext()) {
      sum += reader.next<int64_t>();
    }
    assert(sum == 49858177396);
  }
}
BENCHMARK(LOOP_File_read);

static void LOOP_fstream_File_read(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0, temp;
    std::fstream stream("../benchmark/inp.txt");
    while (stream >> temp) {
      sum += temp;
    }
    assert(sum == 49858177396);
  }
}
BENCHMARK(LOOP_fstream_File_read);

static void LOOP_fscanf_File_read(benchmark::State& state) {
  for (auto _ : state) {
    FILE* fp = fopen("../benchmark/inp.txt", "r");
    int64_t sum = 0, temp;
    while ((fscanf(fp, "%lld", &temp) != EOF)) {
      sum += temp;
    }
    assert(sum == 49858177396);
  }
}
BENCHMARK(LOOP_fscanf_File_read);

int const_val() { return 42; }
int random_val() { return rand(); }

class sensor_gen
    : public gen::base_generator<decltype(const_val())> {
  using T = decltype(const_val());
  T _curr;

 public:
  sensor_gen() { _curr = const_val(); }
  
  bool hasNext() const { return true; }
  T curr() const { return _curr; }
  void next() { _curr = const_val(); }
  MAKE_ITER(sensor_gen, T);
};

class random_gen
    : public gen::base_generator<decltype(random_val())> {
  using T = decltype(random_val());

 private:
  T _curr;

 public:
  random_gen() { _curr = random_val(); }
  
  bool hasNext() const { return true; }
  T curr() const { return _curr; }

  void next() { _curr = random_val(); }
  
  MAKE_ITER(random_gen, T);
};
static void GENERATOR_setvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    auto s_gen = mod::take(state.range(0), sensor_gen());
    auto pipeline = sink::for_each([&](auto i) { val = i; });
    s_gen >>= pipeline;
    assert(val == 42);
  }
}
BENCHMARK(GENERATOR_setvalue)->Arg(1000000LL);

static void LOOP_setvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    for (auto i = 0; i < state.range(0); ++i) {
      val = const_val();
    }
    assert(val == 42);
  }
}
BENCHMARK(LOOP_setvalue)->Arg(1000000LL);

static void GENERATOR_randomvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    auto s_gen = mod::take(state.range(0), random_gen());
    auto pipeline = sink::for_each([&](auto i) { val = i; });
    s_gen >>= pipeline;
    assert(val != 0);
  }
}
BENCHMARK(GENERATOR_randomvalue)->Arg(1000000LL);

static void LOOP_randomvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    for (auto i = 0; i < state.range(0); ++i) {
      val = random_val();
    }
    assert(val != 0);
  }
}
BENCHMARK(LOOP_randomvalue)->Arg(1000000LL);

static void CONST_GENERATOR_many_ops(benchmark::State& state) {
  for (auto _ : state) {
    int64_t acc = 0, sum = 0;
    auto range_gen = gen::range(1000000LL);

    auto transform_pipeline 
    =  pipe::transform([](auto i) { return i % 13; }) 
    >>= pipe::set_state([](auto i, auto _state) { return i + (_state % 9); }, acc) 
    >>= pipe::transform_s([](auto i, auto& _state) { return i + _state; }, acc);

    auto pipeline 
    =   transform_pipeline 
    >>= pipe::partition([](auto i) { return (i % 13) == 0; },
          pipe::transform([](auto i) { return i + 13; }) >>= sink::sum(sum),
          sink::hole()
        );
    range_gen >>= pipeline;
    assert(sum == 2333344);
  }
}
BENCHMARK(CONST_GENERATOR_many_ops);

static void CONST_LOOP_many_ops(benchmark::State& state) {
  for (auto _ : state) {
    int64_t acc = 0, sum = 0;
    for (int64_t i = 0; i < 1000000LL; ++i) {
      int64_t x = (i % 13);
      acc = x + (acc % 9);
      x += acc;
      if ((x % 13) == 0) {
        x += 13;
        sum += x;
      }
    }
    assert(sum == 2333344);
  }
}
BENCHMARK(CONST_LOOP_many_ops);

BENCHMARK_MAIN();