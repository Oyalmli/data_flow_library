#ifndef DVFW_HOLE_HPP
#define DVFW_HOLE_HPP

namespace dvfw {
namespace sink {
class hole : public pipeline_base<hole> {
   public:
    template <typename T>
    void onReceive(T&&) {}
};
}  // namespace sink
}  // namespace dvfw

#endif /* DVFW_HOLE_HPP */