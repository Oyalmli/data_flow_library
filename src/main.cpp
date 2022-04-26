// -*- lsst-c++ -*-
#include <sys/time.h>

#include <chrono>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

#include "dvfw/dvfw.hpp"
#include "sys/resource.h"

using namespace dvfw;

/*
template <typename _IO>
auto pp(_IO& io) { return [&io](int rhs) { io << rhs << '\n'; }; }

auto even = [](auto i) { return i % 2 == 0; };

auto add(int i) { return [=](int j) { return i + j; }; }

template<typename _IO, typename T>
class io_gen : public gen::base_generator<T> {
    private:
    _IO& _io;

    public:
    io_gen(_IO& io) : _io{io} {}

    bool hasNext() {
        return _io.reader.hasNext();
    }

    T next(){
        return _io.reader.template next<T>();
    }
};
*/

template<typename T>
class range : public gen::base_generator<T>{
    public:
    //using value_type = T;
    //using Iterator = gen::GenIterator<range<T>>;
    T _low, _high, _itVal;

    range(T low = 0, T high = 0) : _low{low}, _high{high}, _itVal{low} {}
    
    bool hasNext() { return _itVal < _high; }
    T next() { return _itVal++; }

    //Iterator begin() { return Iterator(this); }
    //Iterator end() { return Iterator(nullptr); }
};


int main() {
    long long sum = 0;
    //auto generator = gen::file<long long>(stdin);
    //auto generator = gen::take(10000000000, gen::value(10));
    auto generator = range(0LL,100LL);

    auto pipeline 
    =   dvfw::sink::for_each([](auto i) { printf("%lld\n", i); });
    
    generator >>= pipeline;

    printf("sum: %lld\n", sum);
}
// rusage info;
//&res, &info,
//  IO io;
//  auto generator = gen::It(io_gen<IO, long long>(io));
//  auto pipeline = sink::for_each([&res, &info, &sum](auto i){
// getrusage(RUSAGE_SELF, &info);
// print_rusage(info);