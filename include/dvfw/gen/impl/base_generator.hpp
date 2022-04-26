#ifndef DVFW_GENERATOR_HPP
#define DVFW_GENERATOR_HPP

#include <thread>

namespace dvfw {
namespace gen {
template <typename T>
class base_generator {
   public:
    virtual T next() = 0;
    virtual bool hasNext() = 0;

    template <typename Pipeline>
    void operator>>=(Pipeline&& pipeline) {
        while (hasNext()) {
            send(next(), pipeline);
        }
    }

    constexpr void wait(int delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_GENERATOR_HPP */