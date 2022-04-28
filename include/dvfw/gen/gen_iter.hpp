/**
 * @file gen_iter.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Base generator implementation class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_GEN_ITER_HPP
#define DVFW_GEN_ITER_HPP

#include <iterator>

namespace dvfw::gen {
template <class Gen, typename T>
class GenIterator : public std::iterator<std::input_iterator_tag, T, bool, T*, T&> {
    Gen* _range;

   public:
   /**
    * @brief Construct a new Gen Iterator object
    * 
    * @param range 
    */
    explicit GenIterator(Gen* range) : _range{range} {};

    GenIterator& operator++() {
        _range->next();
        return *this;
    }

    bool operator!=(GenIterator& other) {
        return _range->hasNext();
    }

    T operator*() {
        return _range->_itVal;
    }
};
};  // namespace dvfw::gen

#endif /* DVFW_BASE_ITER_HPP */