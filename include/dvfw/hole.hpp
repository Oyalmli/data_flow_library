#ifndef DVFW_HOLE_HPP
#define DVFW_HOLE_HPP

#include "dvfw/base.hpp"

namespace dvfw {

class _ : public pipeline_base<_> {
   public:
    template <typename T>
    void onReceive(T&&) {}
};

}  // namespace dvfw

#endif /* DVFW_HOLE_HPP */