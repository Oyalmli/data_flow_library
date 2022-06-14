#include <iostream>
#include <thread>
#include <chrono>

#include "dfl/dfl.hpp"
using namespace dfl;

template<typename T, size_t N>
class Moving_avg {
    public:
    Moving_avg(double delta, size_t skippable) : _total{0}, _delta{delta}, _skippable{skippable} {}

    T update(T sample) {
        return get_avg(sample);
    }

 private:
  T _samples[N];
  size_t _num_samples{0};
  T _total;
  double _delta;
  size_t _skipped{0};
  size_t _skippable;
    T diff(T a, T b) { return a > b ? a - b : b - a; }

  float get_avg(T sample) {
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

int main() {
    struct State {
        double moving_avg = 0;
        double diff = 0;
        double prev = 0;
    } state;
    auto start = std::chrono::high_resolution_clock::now();
    Moving_avg<double, 5> ma(0.5, 1);

    for (auto reading : gen::file<double>(stdin)) {
        state.moving_avg = ma.update(reading);
        state.diff = state.prev > state.moving_avg 
            ? state.prev - state.moving_avg
            : state.moving_avg - state.prev;
        state.prev = reading;
        printf("%d\n", (state.diff > 0.5 ? 1 : 0));
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    printf("Took: %lld", duration);
    //time 1610
}
