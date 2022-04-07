#ifndef DVFW_MOVING_AVERAGE_HPP
#define DVFW_MOVING_AVERAGE_HPP

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"
#include "dvfw/helpers/assignable.hpp"

namespace dvfw {
namespace pipe {
template <typename T, std::size_t N>
class moving_avg : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(FWD(get_avg(values...)), tailPipeline);
    }

    explicit moving_avg() : _total{0} {}

   private:
    T _samples[N];
    size_t _num_samples{0};
    int _total;

    float get_avg(T sample) {
        _total += sample;
        if (_num_samples < N)
            _samples[_num_samples++] = sample;
        else {
            T& oldest = _samples[_num_samples++ % N];
            _total -= oldest;
            oldest = sample;
        }
        return _total / static_cast<float>(std::min(_num_samples, N));
    }
};
}  // namespace pipe
}  // namespace dvfw

#endif /* DVFW_MOVING_AVERAGE_HPP */