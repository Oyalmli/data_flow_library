#ifndef DVFW_ITERATOR_HPP
#define DVFW_ITERATOR_HPP

#include <thread>

namespace dvfw {
namespace gen {
template <typename Gen, typename T>
class base_iterator {
   public:
    virtual Gen begin() = 0;
    virtual Gen end() = 0;
    virtual Gen operator++() = 0;
    virtual Gen operator++(int) = 0;
    virtual bool operator!=(const Gen& it) = 0;
    virtual T operator*() = 0;
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_ITEARATOR_HPP */