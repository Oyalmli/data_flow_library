/**
 * @file push_back.hpp
 * @author Jonathan Boccara
 * @brief Push back sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PUSH_BACK_HPP
#define PUSH_BACK_HPP

#include <functional>

namespace dvfw::sink {
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
/**
 * @brief Pushes the value recieved into the container specified
 * 
 * @tparam Container 
 * @param container 
 * @return push_back_pipeline<Container> 
 */
template <typename Container>
push_back_pipeline<Container> push_back(Container& container) {
    return push_back_pipeline<Container>(container);
}
};  // namespace dvfw::sink

#endif /* PUSH_BACK_HPP */