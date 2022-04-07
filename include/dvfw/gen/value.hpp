#include "base.hpp"
namespace dvfw {
namespace gen {
template <typename T>
class value : public dvfw::gen::base_generator<T> {
   private:
    T _value;

   public:
    value() = default;
    value(T value) : _value{value} {};

    bool hasNext() { return true; }

    T next() {
        return _value;
    }
};
}  // namespace gen
}  // namespace dvfw
