#include "dfl.hpp"
#include <chrono>

using namespace dfl;

int main (){
    {
        int64_t even_sum = 0;
        int64_t odd_sum = 0;
        auto start = std::chrono::high_resolution_clock::now();
        
        gen::range(1'000'000'000)
        >>= pipe::transform(_mod_(13)(_mult(2)))
        >>=  rdir::partition(_even,
            sink::sum(even_sum),
            sink::sum(odd_sum)
        );

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
        printf("[DFL ]:\t%4lldms\n", duration);
        printf(" - Sum of evens: %lld\n - Sum of odds:  %lld\n", even_sum, odd_sum);
    }
    {
        int64_t even_sum = 0;
        int64_t odd_sum = 0;
        auto start = std::chrono::high_resolution_clock::now();

        for (int64_t i = 0; i < 1'000'000'000; ++i) {
            int64_t x = (i*2)%13;
            if ((x&1) == 0) {
                even_sum += x;
            } else {
                odd_sum += x;
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
        printf("[Loop]:\t%4lldms\n", duration);
        printf(" - Sum of evens: %lld\n - Sum of odds:  %lld\n", even_sum, odd_sum);
    }
}
