#include <iostream>
#include <iterator>

template<typename T>
class full_range_gen : public std::iterator<std::input_iterator_tag, T, bool, T*, T&> {
    private:
    T _curr{0}, _max;
    public:
    full_range_gen(T max) : _max{max} {}
    full_range_gen& begin() { return *this; }
    full_range_gen& end()   { return *this; }

    T operator*() {return _curr; }
    full_range_gen& operator++() { ++_curr; return *this; }
    bool operator!=(full_range_gen& o) { return _curr < _max; }
};

int main(){
    auto gen = full_range_gen(10000000000LL);
    int64_t sum = 0;
    for (auto i : gen) {
        sum += i%13;
    }
    std::cout << sum << '\n';
}