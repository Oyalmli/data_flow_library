#ifndef PUSH_BACK_HPP
#define PUSH_BACK_HPP

#include <functional>

#include "dvfw/base.hpp"
#include "dvfw/helpers/FWD.hpp"

namespace dvfw {
namespace sink {
template <typename Container>
class push_back_pipeline : public pipeline_base<push_back_pipeline<Container>> {
   public:
    template <typename T>
    void onReceive(T&& value) {
        container_.get().push_back(FWD(value));
    }

    explicit push_back_pipeline(Container& container) : container_(container) {}

   private:
    std::reference_wrapper<Container> container_;
};

template <typename Container>
push_back_pipeline<Container> push_back(Container& container) {
    return push_back_pipeline<Container>(container);
}
}  // namespace sink
}  // namespace dvfw

#endif /* PUSH_BACK_HPP */