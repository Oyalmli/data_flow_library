#include "dfl/dfl.hpp"
#include <iostream>
#include <iterator>
#include <chrono>

int main(){
    int64_t n, sum = 0;
    std::cin >> n;
    auto start = std::chrono::high_resolution_clock::now();
    //for (int64_t i = 0; i < n; ++i){
    //    sum += i%13;
    //}
   auto range_gen = dfl::gen::range<int64_t>(n);
   //range_gen >>= dfl::sink::for_each([&](auto i){ sum += i%13; });
   range_gen 
   >>= dfl::pipe::transform([](auto i){ return i % 13; }) 
   >>= dfl::sink::sum(sum);
    auto end = std::chrono::steady_clock::now();
    long total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Timing: " << total << '\n';
    std::cout << sum;
}
