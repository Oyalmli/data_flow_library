/**
 * @file sum.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Sum sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/sum.cpp
 */
#ifndef DFL_SINK_SUM_HPP
#define DFL_SINK_SUM_HPP

namespace dfl::sink {
template <typename T>
class sum_pipeline : public pipeline_base<sum_pipeline<T>> {
   public:
    template<typename... V>
    void onReceive(V&&... value) {
        _acc += (value + ...);
    }

    explicit sum_pipeline(T val) : _acc(val) {}

   private:
    T _acc;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
*/
template <typename T>
sum_pipeline<T> sum(T&& val) {
    return sum_pipeline<T>{val};
}
}  // namespace dfl

#endif /* DFL_SINK_SUM_HPP */