/**
 * @file base_iterator.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief abstract base class for itera
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_ITERATOR_HPP
#define DVFW_ITERATOR_HPP

#include <thread>
#include <iterator>

namespace dvfw::gen {
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
};  // namespace dvfw::gen

#endif /* DVFW_ITEARATOR_HPP */