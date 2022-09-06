/**
 * @file dfl.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Entry point for the library
 * 
 * Select which parts of the framework are to be exported
 * 
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DFL_HPP
#define DFL_HPP

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "dfl/gen/impl/base_generator.hpp"

#include "dfl/gen/adjacent.hpp"
#include "dfl/gen/counter.hpp"
#include "dfl/gen/file.hpp"
#include "dfl/mod/noise.hpp"
#include "dfl/mod/flag.hpp"
#include "dfl/mod/random_err.hpp"
#include "dfl/mod/take.hpp"
#include "dfl/mod/repeat.hpp"
#include "dfl/gen/range.hpp"
#include "dfl/gen/sine.hpp"
#include "dfl/gen/value.hpp"
#include "dfl/impl/operator.hpp"
#include "dfl/impl/send.hpp"
#include "dfl/pipe/chunks.hpp"
#include "dfl/pipe/drop.hpp"
#include "dfl/pipe/drop_while.hpp"
#include "dfl/pipe/filter.hpp"
#include "dfl/pipe/fork.hpp"
#include "dfl/pipe/get_var.hpp"
#include "dfl/pipe/intersperse.hpp"
#include "dfl/pipe/moving_avg.hpp"
#include "dfl/pipe/partition.hpp"
#include "dfl/pipe/scanl.hpp"
#include "dfl/pipe/set_state.hpp"
#include "dfl/pipe/set_var.hpp"
#include "dfl/pipe/side_effect.hpp"
#include "dfl/pipe/stride.hpp"
#include "dfl/pipe/take.hpp"
#include "dfl/pipe/tap.hpp"
#include "dfl/pipe/tee.hpp"
#include "dfl/pipe/transform.hpp"
#include "dfl/pipe/transform_s.hpp"
#include "dfl/sink/for_each.hpp"
#include "dfl/sink/hole.hpp"
#include "dfl/sink/histogram.hpp"
#include "dfl/sink/min.hpp"
#include "dfl/sink/max.hpp"
#include "dfl/sink/print.hpp"
#include "dfl/sink/printf.hpp"
#include "dfl/sink/push_back.hpp"
#include "dfl/sink/to_out_stream.hpp"
#include "dfl/sink/set_var.hpp"
#include "dfl/sink/sum.hpp"
#include "dfl/util/IO.hpp"

#include "dfl/gen/mux.hpp"

#include "dfl/helpers/functions.hpp"

namespace dfl {
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
}  // namespace dfl

#endif /* DFL_HPP */
