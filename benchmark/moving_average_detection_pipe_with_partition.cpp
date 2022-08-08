#include <iostream>
#include <thread>

#include "dfl/dfl.hpp"
using namespace dfl;

template <typename T, size_t N>
class restricted_avg : public dfl_base {
 public:
  template <typename... Values, typename TailPipeline>
  void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
    send(FWD(get_avg(values...)), tailPipeline);
  }

  /**
   * @brief Returns a moving average of the last N values
   * @return moving average {double}
   */
  explicit restricted_avg(double delta, size_t skippable)
      : _total{0}, _delta{delta}, _skippable{skippable} {}

 private:
  T _samples[N];
  size_t _num_samples{0};
  T _total;
  double _delta;
  size_t _skipped{0};
  size_t _skippable;

  T diff(T a, T b) { return a > b ? a - b : b - a; }

  double get_avg(T sample) {
    T avg = _total / static_cast<double>(std::min(_num_samples, N));
    if (diff(sample, avg) > _delta && _skipped < _skippable) {
      _skipped++;
      return avg;
    }
    _skipped = 0;
    _total += sample;
    if (_num_samples < N)
      _samples[_num_samples++] = sample;
    else {
      T& oldest = _samples[_num_samples++ % N];
      _total -= oldest;
      oldest = sample;
    }
    return _total / static_cast<double>(std::min(_num_samples, N));
  }
};

template <typename State>
class set_state_pipe : public dfl_base {
 public:
  template <typename Value>
  void onReceive(Value&& value) {
    _state.diff = _state.prev > _state.moving_avg ? _state.prev - _state.moving_avg
                                               : _state.moving_avg - _state.prev;
    _state.prev = value;
    
  }

  /**
   * @brief Returns a moving average of the last N values
   * @return moving average {double}
   */
  set_state_pipe(State state) : _state(state) {}

 private:
  State _state;
};

template <typename State>
set_state_pipe<State> set_state(State&& state) {
    return set_state_pipe<State>{state};
}

int main() {
  struct State {
    double moving_avg = 0;
    double diff = 0;
    double prev = 0;
  } state;
  auto start = std::chrono::high_resolution_clock::now();
  auto file_gen = gen::file<double>(stdin);

  auto set_moving_avg 
  =   restricted_avg<double, 4>(0.5, 1) 
  >>= pipe::set_state([](auto f, auto state) { return f; }, state.moving_avg) 
  >>= sink::hole();

  file_gen 
  >>= pipe::tee(pipe::fork(
    pipe::partition([](auto i){ return i < 14 || i > 30; }, sink::hole(), set_moving_avg),
    set_state(state) ))
  >>= pipe::transform_s([](auto f, State& state) { return state.diff > 0.5 ? 1 : 0; }, state)
  >>= sink::printf("%d\n");
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
  printf("Took: %lld", duration);
  //took 1384
}
