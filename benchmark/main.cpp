#include <iostream>
#include <thread>

#include "dfl/dfl.hpp"
using namespace dfl;

/*
template <typename T>
class base_generator {
 public:
  using value_type = T;
  virtual bool hasNext() { return true; }
  virtual T curr() = 0;
  virtual T next() = 0;
  template <typename Pipeline>
  void operator>>=(Pipeline&& pipeline) {
    for(;hasNext(); next()) {
      dfl::send(curr(), pipeline);
    }
  }
};

template<typename T>
class range : public base_generator<T> {
  T _curr{0}, _max;
 public:
  range(T max) : _max{max} {}
  bool hasNext() { return _curr < _max; }
  T curr() { return _curr; }
  T next() { ++_curr; return _curr; }
};

int main() {
  int64_t sum = 0;
  auto r = gen::range(10000000000);
  r >>= sink::sum(sum);

  std::cout << sum << '\n';
}
*/

/*
int main() {
  auto char_gen = gen::file<char>(stdin);
  int64_t sum = 0;
  int num = 0;

  auto update_num 
  = pipe::transform([](auto c){ return c - '0'; })
  >>= pipe::set_state([](auto n, auto& _num){ _num = _num * 10 + n; }, num)
  >>= sink::hole();

  auto add_num 
  = pipe::transform_s([](auto _, auto& _num){ return _num; }, num)
  >>= pipe::side_effect([&num](){ num = 0; })
  >>= sink::sum(sum);

  auto sum_numbers
  = pipe::partition([](auto c){ return c >= '0' && c <= '9'; },
      update_num,
      add_num
  );

  char_gen >>= sum_numbers;

  std::cout << sum << '\n';
}
*/
/*
int main() {
  auto range = gen::range(100);

  auto transform
  =   pipe::transform([](auto i){ return i*2; })
  >>= pipe::transform([](auto i){ return i+1; });

  range >>= transform >>= sink::print('\n');
}
*/
/*
int const_val() { return 42; }

class const_gen
    : public gen::base_generator<const_gen, decltype(const_val())> {
  using T = decltype(const_val());
  T _curr;

 public:
  const_gen() { _curr = const_val(); }
  IT(const_gen, T);
  bool hasNext() { return true; }
  T curr() { return _curr; }
  T next() { _curr = const_val(); return _curr; }
};

struct const_gen_s : public std::iterator<std::input_iterator_tag, int, bool, int*, int&> {
  int curr;
  size_t to_take, taken{0};

  const_gen_s(size_t take) : to_take{take} { curr = const_val(); }
  const_gen_s& begin() { return *this; }
  const_gen_s& end() { return *this; }
  const_gen_s& operator++() { curr = const_val(); ++taken; return *this; }
  int operator*() { return curr; }
  bool operator!=(const const_gen_s& o) { return taken < to_take; }
};

void reassingn (size_t iters, int* x) {
  for (size_t i = 0; i < iters; ++i) { *x = 42; }
}
*/
template <typename F, class Gen>
class stop_gen : public gen::base_generator<stop_gen<F, Gen>, typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen;
  F _test;
  T _curr{0};
  
 public:

  stop_gen() = default;
  stop_gen(F test, Gen generator)
      : _gen{generator}, _test{test} {}
  
  using this_class = stop_gen<F, Gen>;
  IT(this_class, T);

  bool hasNext() { return _gen.hasNext() && _test(_curr); }

  T next() {
    _curr = _gen.next();
    return _curr;
  }

  T curr() { return _curr; }
};

static constexpr uint64_t range_mod_sum(){
  uint64_t num = 0;
  for(uint64_t i = 0; i < 100ULL; ++i){
    num += i%13;
  }
  return num;
}

int main(){
  std::cout << range_mod_sum();
}
