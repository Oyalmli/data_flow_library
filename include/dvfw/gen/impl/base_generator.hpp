/**
 * @file base_generator.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief abstract base class for the generators
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_GENERATOR_HPP
#define DVFW_GENERATOR_HPP

#include <thread>

namespace dvfw::gen {
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
};  // namespace dvfw::gen

#endif /* DVFW_GENERATOR_HPP */