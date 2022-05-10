/**
 * @file for_each.hpp
 * @author Jonathan Boccara
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example for_each.cpp
 */
#ifndef DFL_CUSTOM_INSERTER_HPP
#define DFL_CUSTOM_INSERTER_HPP

namespace dfl::sink {
template <typename Function>
class for_each_pipeline : public pipeline_base<for_each_pipeline<Function>> {
   public:
    template <typename... T>
    void onReceive(T&&... value) {
        function_(FWD(value)...);
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
}  // namespace dfl

#endif /* DFL_CUSTOM_INSERTER_HPP */