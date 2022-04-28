#include "dvfw/dvfw.hpp"

using namespace dvfw;

template <typename T>
class range {
   public:
    using value_type = T;
    using Iterator = gen::GenIterator<range<T>, T>;
    T _low, _high, _itVal;

    range(T low = 0, T high = 0) : _low{low}, _high{high}, _itVal{low} {}

    bool hasNext() { return _itVal < _high; }
    T next() { return _itVal++; }

    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); }
};

struct Count : public gen::base_generator<long long> {
   public:
    using Iterator = gen::GenIterator<Count, long long>;
    long long _itVal{0};
    long long next() { return _itVal++; }
    bool hasNext() { return _itVal < __LONG_LONG_MAX__; }
    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); } 
};

int main() {
    long long sum = 0;
    auto generator = gen::take(1000000000, Count());
    //auto generator = gen::range(1000000000LL);
    auto pipeline = sink::for_each([&sum](auto i){ sum += i; });
    generator >>= pipeline;
    printf("%lld\n", sum); 
}

//#include "sys/resource.h"
// rusage info;
// &res, &info,
// IO io;
// auto generator = gen::It(io_gen<IO, long long>(io));
// auto pipeline = sink::for_each([&res, &info, &sum](auto i){
// getrusage(RUSAGE_SELF, &info);
// print_rusage(info);