#include <deque>
#include <iostream>
#include <vector>

#include "dvfw/dvfw.hpp"

struct State {
    int max;
    int min;
    std::deque<int> last3;
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> res = {};

    State state = {
        .max = 0,
        .min = 0,
        .last3 = {}};


    
    auto pip = dvfw::set_state(
        [](int i, State& st) {
            if (st.last3.size() < 3) { st.last3.push_front(i); } 
            else { st.last3.pop_back(); st.last3.push_front(i); }
        }, state) 
    >>= dvfw::transform_s(
        [](int i, State& st) {
            return i + st.last3.front();
        },state) 
    >>= dvfw::push_back(res);
    
    std::vector<int> vecCopy;
    for (int idx = 0; idx < vec.size(); idx++) {
        vecCopy.assign(vec.begin() + idx, vec.end());
        vecCopy >>= pip;
        std::cout << "\n";
        for (auto i : res) {
            std::cout << i << "\n";
        }
    }

    
}