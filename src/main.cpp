#include <iostream>
#include <vector>
#include <numeric>

int main(){
  std::vector<int64_t> llvec(1000000);
  std::iota(llvec.begin(), llvec.end(), 0LL);
  int64_t sum = std::accumulate(llvec.begin(), llvec.end(), 0);
  std::cout << sum << '\n';
}
