/**
 * @file moving_avg.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Moving average pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/moving_avg.cpp
 */
#ifndef DFL_MOVING_AVERAGE_HPP
#define DFL_MOVING_AVERAGE_HPP

namespace dfl {
namespace pipe {
template <typename T, std::size_t N>
class moving_avg : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(FWD(get_avg(values...)), tailPipeline);
    }

    /**
     * @brief Returns a moving average of the last N values
     * @return moving average {double}
     */
    explicit moving_avg() : _total{0} {}

   private:
    T _samples[N];
    size_t _num_samples{0};
    T _total;

    double get_avg(T sample) {
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
}  // namespace pipe
}  // namespace dfl

#endif /* DFL_MOVING_AVERAGE_HPP */