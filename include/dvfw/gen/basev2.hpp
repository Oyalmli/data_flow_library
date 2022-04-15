#ifndef DVFW_GEN_HPP
#define DVFW_GEN_HPP

#include <thread>

namespace dvfw {
namespace gen {

template <typename Gen, typename T>
class gen_it : public std::iterator<std::input_iterator_tag, T> {
   private:
    Gen _generator;
    T _curr;

   public:
    gen_it(Gen generator) : _generator{generator} {
        _curr = _generator.next();
    }

    gen_it begin() {
        return *this;
    }
    gen_it end(){
        return *this;
    }
    gen_it operator++(){
        _curr = _generator.next();
        return *this;
    }

    bool operator!=(const gen_it& it){
        return _generator.hasNext();
    }

    T operator*(){
        return _curr;
    }
};

};  // namespace gen
};  // namespace dvfw

#endif /* DVFW_GEN_HPP */