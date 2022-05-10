#include <vector>

#include "../catch.hpp"
#include "dfl/dfl.hpp"

using namespace dfl;

template <typename T>
class range_gen : public dfl::gen::base_generator<range_gen<T>, T> {
   private:
    T _min, _max, _step, _curr;

   public:
    range_gen() = default;
    range_gen(T min, T max) : _min{min}, _max{max}, _step{1}, _curr{min} {};

    bool hasNext() {
        return _max > _curr;
    }

    T next() {
        T temp = _curr;
        _curr += _step;
        return temp;
    }
};

const std::string prefix = "[IMPL_GENERATOR]: ";

/*
TEST_CASE(prefix + "able to create own generator") {
    std::vector<int> expected = {1, 2, 3, 4, 5};
    std::vector<int> res = {};

    auto range_generator = gen::It(range_gen(1, 6));

    range_generator >>= sink::push_back(res);

    REQUIRE(res == expected);
}
*/