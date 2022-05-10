#include <iostream>
#include <vector>

#include "dfl/dfl.hpp"

//#include "sys/resource.h"
// rusage info;
// &res, &info,
// IO io;
// auto generator = gen::It(io_gen<IO, long long>(io));
// auto pipeline = sink::for_each([&res, &info, &sum](auto i){
// getrusage(RUSAGE_SELF, &info);
// print_rusage(info);

using namespace dfl;

union pin_t {
  int pin;
  long pin;
};

int sensor_read(pin_t pin) {
  return 0;
}

class sensor_gen : public gen::base_generator<x, int> {
  int _curr;
  pin_t _sensor_pin;
  public:
  sensor_gen(pin_t sensor_pin) : _sensor_pin{sensor_pin} {
    _curr = sensor_read(sensor_pin);
  };

  bool hasNext(){ return true; }
  int curr() {return _curr; }
  int next() {
    _curr = sensor_read(_sensor_pin);
    return _curr;
  };
};

class x : public gen::base_generator<x, int> {
  int _curr{0};

 public:
  bool hasNext() { return true; }
  int next() { return _curr++; }
  int curr() { return _curr; }
  IT(x, int);
};

int main() {
  long long sum = 0;

  auto l = gen::take(10000000, gen::sine(0.01, 1.0, 0.0));
  auto r = x();

  auto rg = gen::mux(l, r);
  rg >>= sink::for_each([](auto i, auto j) { printf("[%8d]: %f\n", j, i); });
  // rg >>= sink::for_each([&sum](auto i) { sum += i; });

  // printf("%lld\n", sum);
}
