/**
 * @file for_each.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example for_each.cpp
 */
#ifndef DVFW_CUSTOM_INSERTER_HPP
#define DVFW_CUSTOM_INSERTER_HPP

namespace dvfw::sink {
template <typename Function>
class for_each_pipeline : public pipeline_base<for_each_pipeline<Function>> {
   public:
    template <typename T>
    void onReceive(T&& value) {
        function_(FWD(value));
    }

    explicit for_each_pipeline(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
*/
template <typename InsertFunction>
for_each_pipeline<InsertFunction> for_each(InsertFunction insertFunction) {
    return for_each_pipeline<InsertFunction>(insertFunction);
}
};  // namespace dvfw

#endif /* DVFW_CUSTOM_INSERTER_HPP */