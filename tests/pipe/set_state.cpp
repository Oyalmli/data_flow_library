#include "../catch.hpp"
#include "dvfw/dvfw.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
using namespace dvfw;
const std::string prefix = "[SET STATE]: ";

struct State {
    int val;
};

template<typename T>
void max(T i, State& state){ 
    if (i > state.val) {
        state.val = i;
    }
}

TEST_CASE(prefix + "able to set part of state")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    State init_state = { .val=0 };
    State expected_state = { .val=10 };
    input 
    >>= pipe::set_state(max<int>, init_state)
    >>= sink::hole();
    REQUIRE(init_state.val == expected_state.val);
}

TEST_CASE(prefix + "static state is applied")
{
    auto const input    = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9,10};
    auto const expected = std::vector<int>{4, 5, 6, 7, 8, 9,10,11,12,13};
    auto result = std::vector<int>{};

    State state = { .val=3 };

    input 
    >>= pipe::transform_s([](int i, State state){ return i + state.val; }, state)
    >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}

TEST_CASE(prefix + "able to use state in transform")
{
    auto const input = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const expected = std::vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    auto result = std::vector<int>{};

    State state = { .val=0 };

    input 
    >>= pipe::set_state(max<int>, state)
    >>= pipe::transform_s([](int i, State state){ return i + state.val; }, state)
    >>= sink::push_back(result);
    
    REQUIRE(result == expected);
}
