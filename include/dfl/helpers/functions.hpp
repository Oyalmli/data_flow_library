#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

namespace dfl {
// MK MACRO
// MK(NAME, FUNCTION)
// In function, State = State of class, O = the other incoming variable
#define MK(NAME, FUNC)                                 \
  template <typename State>                            \
  class f##NAME {                                      \
   public:                                             \
    f##NAME(State&& state) : _state(state) {}          \
                                                       \
    template <typename O>                              \
    auto operator()(O o) const {                       \
      return FUNC;                                     \
    }                                                  \
    State _state;                                      \
  };                                                   \
  template <typename State>                            \
  f##NAME<State> NAME(State&& state) {                 \
    return f##NAME<State>{std::forward<State>(state)}; \
  }
auto _id = [](auto x){ return x; };
auto _not = [](auto x) { return !x; };
auto _not_ = [](auto g) { return [=](auto x) { return !g(x); }; };
auto _even = [](auto x) { return (x & 1) == 0; };
auto _even_ = [](auto g) { return [=](auto x) { return (g(x) & 1) == 0; }; };
auto _odd = [](auto x) { return (x & 1) == 1; };
auto _odd_ = [](auto g) { return [=](auto x) { return (g(x) & 1) == 1; }; };
auto _negate = [](auto x) { return -x; };
auto _negate_ = [](auto g) { return [=](auto x) { return -g(x); }; };
MK(_equal, o == _state);
MK(_equal_, [=](auto x) { return (f(x) == _state); });
MK(_greater_than, o > _state);
MK(_greater_than_, [=](auto x) { auto r = o(x); return r > _state; });
MK(_greater_than_equal, o >= _state);
MK(_greater_than_equal_, [=](auto x) { return (o(x) >= _state); });
MK(_less_than, o < _state);
MK(_less_than_, [=](auto x) { return (o(x) < _state); });
MK(_less_than_equal, o <= _state);
MK(_less_than_equal_, [=](auto x) { return (o(x) <= _state); });
MK(_addValue, o + _state);
MK(_addValue_, [=](auto x) { return o(x) + _state; });
MK(_subValue, o - _state);
MK(_subValue_, [=](auto x) { return o(x) - _state; });
MK(_mult, o* _state);
MK(_mult_, [=](auto x) { return o(x) * _state; });
MK(_mod, o % _state);
MK(_mod_, [=](auto x) { return o(x) % _state; });
MK(_constant, _state);

auto _between = [](auto a, auto b) {
  return [=](auto x) { return a <= x && x <= b; };
};
auto _outside = [](auto a, auto b) {
  return [=](auto i) { return i < a || i > b; };
};

auto _add = [](auto a, auto b) { return a + b; };
auto _add_ = [](auto g) { return [=](auto a, auto b) { return g(a) + b; }; };
auto _max = [](auto a, auto b) { return a > b ? a : b; };
auto _max_ = [](auto g) {
  return [=](auto a, auto b) { return g(a) > b ? g(a) : b; };
};
auto _print = [](auto a) { return std::cout << a << '\n'; };
auto _print_ = [](auto g) {
  return [=](auto a) { std::cout << g(a) << "\n"; };
};
/*
auto _not = [](auto a) { return !a; };
auto _not_ = [](auto g) { return [=](auto x) { return !g(x); }; };
auto _equal = [](auto n) { return [=](auto x) { return x == n; }; };
auto _equal_ = [](auto n) { return [=](auto f) { return [=](auto x) { return
(f(x) == n); }; }; };

auto _even = [](auto a) { return (a&1) == 0; };
auto _even_ = [](auto g) { return [=](auto x) { return (g(x)&1) == 0; }; };
auto _odd = [](auto a) { return (a&1) == 1; };
auto _odd_ = [](auto g) { return [=](auto x) { return (g(x)&1) == 1; }; };

auto _greater_than = [](auto& n) { return [=](auto x) { return x > n; }; };
auto _greater_than_ = [](auto n) { return [=](auto f) { return [=](auto x) {
return (f(x) > n); }; }; }; auto _greater_than_equal = [](auto n) { return
[=](auto f) { return [=](auto x) { return (f(x) > n); }; }; }; auto
_greater_than_equal_ = [](auto n) { return [=](auto f) { return [=](auto x) {
return (f(x) >= n); }; }; }; auto _less_than = [](auto n) { return [=](auto x) {
return x < n; }; }; auto _less_than_ = [](auto n) { return [=](auto f) { return
[=](auto x) { return (f(x) < n); }; }; }; auto _less_than_equal = [](auto n) {
return [=](auto x) { return x <= n; }; }; auto _less_than_equal_ = [](auto n) {
return [=](auto f) { return [=](auto x) { return (f(x) <= n); }; }; };

auto _add = [](auto a, auto b){ return a + b; };
auto _add_ = [](auto g) { return [=](auto a, auto b) { return g(a)+b; }; };
auto _addValue = [](auto n) { return [=](auto x) { return x+n; }; };
auto _addValue_ = [](auto n) { return [=](auto f) { return [=](auto x) { return
(f(x)+n); }; }; }; auto _mod = [](auto n) { return [=](auto x) { return x % n;
}; }; auto _negate = [](auto a) { return -a; }; auto _negate_ = [](auto g) {
return [=](auto x) { return -g(x); }; };

auto _max = [](auto a, auto b){ return a > b ? a : b; };
auto _max_ = [](auto g) { return [=](auto a, auto b) { return g(a) > b ? g(a) :
b; }; };

auto _print = [](auto a) { return std::cout << a << '\n'; };
auto _print_ = [](auto g) { return [=](auto a) { std::cout << g(a) << "\n"; };
};
*/
}  // namespace dfl
#endif