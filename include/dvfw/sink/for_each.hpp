#ifndef DVFW_CUSTOM_INSERTER_HPP
#define DVFW_CUSTOM_INSERTER_HPP

namespace dvfw {
namespace sink {
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
}  // namespace sink
}  // namespace dvfw

#endif /* DVFW_CUSTOM_INSERTER_HPP */