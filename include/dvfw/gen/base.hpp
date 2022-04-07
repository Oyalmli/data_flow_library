#ifndef DVFW_GENERATOR_HPP
#define DVFW_GENERATOR_HPP

#include <cstdlib>
#include <ctime>
#include <thread>

#include "../dvfw.hpp"

namespace dvfw {
namespace gen {
template <typename T>
class base_generator {
   public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;

    template <typename Pipeline>
    void operator>>=(Pipeline&& pipeline) {
        while (hasNext()) {
            dvfw::send(next(), pipeline);
        }
    }

    void wait(int delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_GENERATOR_HPP */