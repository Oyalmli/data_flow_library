#include <benchmark/benchmark.h>
#include <random>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "dfl/dfl.hpp"

using namespace dfl;

template<typename T>
class file_fstream_gen : public gen::base_generator<file_fstream_gen<T>, T>{
    std::fstream _stream;
    T _curr;

    public:
    file_fstream_gen(const char* path) : _stream {path} {
      _stream >> _curr;
    }
    IT(file_fstream_gen<T>, T);
    bool hasNext(){ return !_stream.eof(); }
    T next() {
        _stream >> _curr;
        return _curr; }
    T curr() { return _curr; }
};

class file_fscanf_gen : public gen::base_generator<file_fscanf_gen, int64_t>{
    FILE* _fp;
    int64_t _curr;
    bool _more = true;

    public:
    file_fscanf_gen(const char* path) {
        _fp = fopen(path, "r");
        fscanf(_fp, "%lld", &_curr);
    }
    IT(file_fscanf_gen, int64_t);
    bool hasNext(){ return _more; }
    int64_t next() {
        _more = (fscanf(_fp, "%lld", &_curr) != EOF);
        return _curr; }
    int64_t curr() { return _curr; }
};

/////////////////////////
//      GENERATORS     //
/////////////////////////
static void GENERATOR_File_read(benchmark::State& state) {
  for (auto _ : state) {
    FILE* fp =
        fopen("/Users/oyvind/master/data_flow_library/benchmark/inp.txt", "r");
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
    auto inp_gen = file_fstream_gen<int64_t>("/Users/oyvind/master/data_flow_library/benchmark/inp.txt");
    auto pipeline = sink::sum(sum);
    inp_gen >>= pipeline;
    assert(sum == 49858177396);
  }
}
BENCHMARK(GENERATOR_fstream_File_read);

static void GENERATOR_fscanf_File_read(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto inp_gen = file_fscanf_gen("/Users/oyvind/master/data_flow_library/benchmark/inp.txt");
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
      FILE* fp =
        fopen("/Users/oyvind/master/data_flow_library/benchmark/inp.txt", "r");
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
    std::fstream stream("/Users/oyvind/master/data_flow_library/benchmark/inp.txt");
    while (stream >> temp) {
        sum += temp;
    }
    assert(sum == 49858177396);
  }
}
BENCHMARK(LOOP_fstream_File_read);

static void LOOP_fscanf_File_read(benchmark::State& state) {
  for (auto _ : state) {
      FILE* fp =
        fopen("/Users/oyvind/master/data_flow_library/benchmark/inp.txt", "r");
    int64_t sum = 0, temp;
    while ((fscanf(fp, "%lld", &temp) != EOF)) {
        sum += temp;
    }
    assert(sum == 49858177396);
  }
}
BENCHMARK(LOOP_fscanf_File_read);

int sensor_read() {
    return 42;
}

int random_read() {
    return rand();
}

class sensor_gen : public gen::base_generator<sensor_gen, decltype(sensor_read())> {
    using T = decltype(sensor_read());

    private:
    T _curr;

    public:
    sensor_gen(){
        _curr = sensor_read();
    }
    IT(sensor_gen, T);
    bool hasNext() { return true; }
    T curr() { return _curr; }
    T next() {
        _curr = sensor_read();
        return _curr;
    }    
};

class random_gen : public gen::base_generator<random_gen, decltype(random_read())> {
    using T = decltype(random_read());

    private:
    T _curr;

    public:
    random_gen(){
        _curr = random_read();
    }
    IT(random_gen, T);

    bool hasNext() { return true; }

    T curr() { return _curr; }

    T next() {
        _curr = random_read();
        return _curr;
    }    
};
static void GENERATOR_setvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    auto s_gen = mod::take(state.range(0), sensor_gen());
    auto pipeline = sink::for_each([&](auto i){ val = i; });
    s_gen >>= pipeline;
    assert(val == 42);
  }
}
BENCHMARK(GENERATOR_setvalue)->Arg(1000000LL);

static void LOOP_setvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    for (auto i = 0; i < state.range(0); ++i) {
        val = sensor_read();
    }
    assert(val == 42);
  }
}
BENCHMARK(LOOP_setvalue)->Arg(1000000LL);

static void GENERATOR_randomvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    auto s_gen = mod::take(state.range(0), random_gen());
    auto pipeline = sink::for_each([&](auto i){ val = i; });
    s_gen >>= pipeline;
    assert(val != 0);
  }
}
BENCHMARK(GENERATOR_randomvalue)->Arg(1000000LL);

static void LOOP_randomvalue(benchmark::State& state) {
  for (auto _ : state) {
    auto val = 0;
    for (auto i = 0; i < state.range(0); ++i) {
        val = random_read();
    }
    assert(val != 0);
  }
}
BENCHMARK(LOOP_randomvalue)->Arg(1000000LL);

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