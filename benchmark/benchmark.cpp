#include <benchmark/benchmark.h>
#include <fstream>
#include <cstdio>
#include <iostream>

#include "dfl/dfl.hpp"

using namespace dfl;

template<typename T>
class file_ifstream_gen : public gen::base_generator<file_ifstream_gen<T>, T>{
    std::fstream _stream;
    T _curr;

    public:
    file_ifstream_gen(const char* path) : _stream {path} {
        _stream >> _curr;
    }
    IT(file_ifstream_gen<T>, T);
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

static void RANGE_File_read(benchmark::State& state) {
  for (auto _ : state) {
    FILE* fp =
        fopen("/Users/oyvind/master/data_flow_library/benchmark/inp.txt", "r");
    int64_t sum = 0;
    auto inp_gen = gen::file<int64_t>(fp);
    auto pipeline = sink::sum(sum);
    inp_gen >>= pipeline;
    assert(sum == 499999500000);
  }
}
BENCHMARK(RANGE_File_read);

static void RANGE_fstream_File_read(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto inp_gen = file_ifstream_gen<int64_t>("/Users/oyvind/master/data_flow_library/benchmark/inp.txt");
    auto pipeline = sink::sum(sum);
    inp_gen >>= pipeline;
    assert(sum == 499999500000);
  }
}
BENCHMARK(RANGE_fstream_File_read);

static void RANGE_fscanf_File_read(benchmark::State& state) {
  for (auto _ : state) {
    int64_t sum = 0;
    auto inp_gen = file_fscanf_gen("/Users/oyvind/master/data_flow_library/benchmark/inp.txt");
    auto pipeline = sink::sum(sum);
    inp_gen >>= pipeline;
    assert(sum == 499999500000);
  }
}
BENCHMARK(RANGE_fscanf_File_read);

BENCHMARK_MAIN();