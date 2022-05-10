#include <chrono>
#include <iostream>
#include <thread>
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
/****************** CREATING A GENERATOR ******************/
/*
class sensor_generator
    : public dfl::gen::base_generator<sensor_generator, int> {
  int _curr;
  pin_t _sensor_pin;

 public:
  sensor_generator(pin_t sensor_pin) : _sensor_pin{sensor_pin} {
    _curr = sensor_read(sensor_pin);
  };
  IT(sensor_generator, int);

  bool hasNext() { return true; }
  int curr() { return _curr; }
  int next() {
    _curr = sensor_read(_sensor_pin);
    return _curr;
  };
};
*/
/*****************************************************/

/****************** CREATING A PIPE ******************/
template <typename duration_t>
class sleep_pipe : public dfl_base {
  duration_t _sleep_duration;

 public:
  template <typename... Values, typename TailPipeline>
  void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
    // Sends the value/values to the tailPipeline using std::forward
    send(FWD(values)..., tailPipeline);
    std::this_thread::sleep_for(_sleep_duration);
  }

  sleep_pipe(duration_t sleep_duration) : _sleep_duration{sleep_duration} {}
};
/*****************************************************/

int main() {
  auto sine_gen = gen::take(10000000, gen::sine(0.01, 1.0, 0.0));
  auto count_gen = gen::counter<long long>();

  auto sine_count_gen = gen::mux(sine_gen, count_gen);

  sine_count_gen
  >>= sleep_pipe(std::chrono::milliseconds(100))
  >>= pipe::transform([](auto sine_val, auto idx){ return std::tuple{ sine_val-1.0, idx }; })
  >>= sink::for_each([](auto tup) {
    auto& [sine_val, idx] = tup;
    printf("[%8lld]: %f\n", idx, sine_val); 
  });
}
