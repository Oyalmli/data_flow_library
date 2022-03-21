#ifndef DVFW_GENERATOR_HPP
#define DVFW_GENERATOR_HPP

#include <cstdlib>
#include <ctime>
#include <thread>

namespace dvfw {
namespace gen {
template <typename T>
class base_generator {
   public:
    bool hasNext();

    T next();

    template <typename Pipeline>
    void operator>>=(Pipeline&& pipeline);

    void wait(int delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_GENERATOR_HPP */