/**
 * @file range.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Range generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_GEN_RANGE_HPP
#define DVFW_GEN_RANGE_HPP

namespace dvfw {
namespace gen {
template <typename T>
class range {
   public:
    using value_type = T;
    using Iterator = GenIterator<range<T>, T>;

   private:
    T _min, _max, _step, _curr;

   public:
    T _itVal;

    /**
     * @brief Construct a range generator
     * 
     */
    range() = default;
    range(T max) : _min{0}, _max{max}, _step{1}, _curr{0}, _itVal{0} {};
    range(T min, T max) : _min{min}, _max{max}, _step{1}, _curr{min}, _itVal{min} {};
    range(T min, T max, T step) : _min{min}, _max{max}, _step{step}, _curr{min}, _itVal{min} {};

    bool hasNext() {
        return _max > _curr;
    }

    T next() {
        _curr += _step;
        _itVal = _curr;
        return _itVal;
    }

    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); }
};
}  // namespace gen
}  // namespace dvfw

#endif  // DVFW_GEN_RANGE_HPP
