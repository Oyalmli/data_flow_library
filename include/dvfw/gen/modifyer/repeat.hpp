/**
 * @file take.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Repeat generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GEN_MOD_REPEAT_HPP
#define GEN_MOD_REPEAT_HPP

namespace dvfw::gen {
template <class Gen>
class repeat {
   private:
    Gen _gen_init;
    Gen _gen;

   public:
    using value_type = decltype(_gen.next());
    using Iterator = gen::GenIterator<repeat<Gen>, value_type>;

    value_type _itVal = _gen._itVal;

    repeat(Gen generator) : _gen_init{generator}, _gen{generator} {}

    /**
     * @brief Repeats the generator
     *
     * @return bool
     */
    bool hasNext() {
        return true;
    }

    decltype(_gen.next()) next() {
        _gen.next();
        if(!_gen.hasNext()) {
            _gen = _gen_init;
        }
        _itVal = _gen._itVal;
        return _gen._itVal;
    }

    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); }
};
};  // namespace dvfw::gen

#endif  // GEN_MOD_REPEAT_HPP
