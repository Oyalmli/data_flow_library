#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

namespace dfl {
    auto _not_ = [](auto a) { return !a; };
    auto _not__ = [](auto g) { return [=](auto x) { return !g(x); }; };
    auto _even = [](auto a) { return (a%2)==0; };
    auto _even_ = [](auto g) { return [=](auto x) { return (g(x)%2)==0; }; };

    auto _greater_than = [](auto n) { return [=](auto x) { return x > n; }; };
    auto _greater_than_ = [](auto n) { return [=](auto f) { return [=](auto x) { return (f(x) > n); }; }; };
    auto _greater_than_equal = [](auto n) { return [=](auto f) { return [=](auto x) { return (f(x) > n); }; }; };
    auto _greater_than_equal_ = [](auto n) { return [=](auto f) { return [=](auto x) { return (f(x) >= n); }; }; };
    auto _less_than = [](auto n) { return [=](auto x) { return x < n; }; };
    auto _less_than_ = [](auto n) { return [=](auto f) { return [=](auto x) { return (f(x) < n); }; }; };
    auto _less_than_equal = [](auto n) { return [=](auto x) { return x <= n; }; };
    auto _less_than_equal_ = [](auto n) { return [=](auto f) { return [=](auto x) { return (f(x) <= n); }; }; };

    auto _add = [](auto a, auto b){ return a + b; };
    auto _add_ = [](auto g) { return [=](auto a, auto b) { return g(a)+b; }; };
    auto _addValue = [](auto n) { return [=](auto x) { return x+n; }; };
    auto _addValue_ = [](auto n) { return [=](auto f) { return [=](auto x) { return (f(x)+n); }; }; };
    auto _mod = [](auto n) { return [=](auto x) { return x % n; }; };
    auto _negate = [](auto a) { return -a; };
    auto _negate_ = [](auto g) { return [=](auto x) { return -g(x); }; };

    auto _max = [](auto a, auto b){ return a > b ? a : b; };
    auto _max_ = [](auto g) { return [=](auto a, auto b) { return g(a) > b ? g(a) : b; }; };

    auto _print = [](auto a) { return std::cout << a << '\n'; };
    auto _print_ = [](auto g) { return [=](auto a) { std::cout << g(a) << "\n"; }; };
} // namespace dfl::functions
#endif