/**
 * @file take.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Take generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GEN_MOD_TAKE_HPP
#define GEN_MOD_TAKE_HPP

namespace dvfw::gen {
template <class Gen>
class take {
   private:
    Gen _gen;
    size_t _num;
    size_t _taken{0};

   public:
    using value_type = decltype(_gen.next());
    using Iterator = gen::GenIterator<take<Gen>, value_type>;

    value_type _itVal = _gen._itVal;

    take(size_t num, Gen generator) : _gen{generator}, _num{num} {}

    /**
     * @brief Return true of the generator has more values, and not enough values have been taken
     *
     * @return bool
     */
    bool hasNext() {
        return _gen.hasNext() && (_taken < _num);
    }

    decltype(_gen.next()) next() {
        _taken++;
        _gen.next();
        _itVal = _gen._itVal;
        return _gen._itVal;
    }

    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); }
};
};  // namespace dvfw::gen

#endif  // GEN_MOD_TAKE_HPP
