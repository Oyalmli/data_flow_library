/**
 * @file value.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Value generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_GEN_VALUE_HPP
#define DVFW_GEN_VALUE_HPP

namespace dvfw {
namespace gen {

template <typename T>
class value : public base_generator<T> {
    public:
    using value_type = T;
    using Iterator = GenIterator<value<T>, T>;
    T _itVal;

    /**
     * @brief Repeats the set value
     * 
     * @param value to be repeated 
     */
    value(T value = 0) : _itVal{value} {};

    /**
     * @brief Returns true if the generator has more values 
     * 
     * @return true
     */
    bool hasNext() { return true; }

    /**
     * @brief The next value from the iterator
     * 
     * @return T 
     */
    T next() {
        return _itVal;
    }


    /// @brief Creates and returns an Iterator for the value generator
    /// @return Iterator 
    /// @param none
    Iterator begin() { return Iterator(this); }

    /**
     * @brief Returns a nullPtr Iterator
     * 
     * @return Iterator 
     */
    Iterator end() { return Iterator(nullptr); }
};
}  // namespace gen
}  // namespace dvfw

#endif
