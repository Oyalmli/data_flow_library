#include <iostream>

#include "dfl/dfl.hpp"

using namespace dfl;
using namespace std::chrono;

int main() {

  double movingAvg = 0;
  double diff = 0;
  double prev = 0;

  int64_t ssum = 0;
  int64_t count = 0;
  auto start = high_resolution_clock::now();
  /*
  gen::file<double>(stdin)
  >>= pipe::tee(
    pipe::fork(
      pipe::side_effect([&count](){ ++count; }) >>= sink::hole() // FOR TESTINK PURPUSS
      ,
      pipe::partition(_outside(14,30),
        sink::hole(), 
        restricted_avg<double, 4>(0.5, 1) 
        >>= sink::set_var(movingAvg)
      )
      ,
      pipe::get_var(prev)
      >>= pipe::partition(_greater_than(movingAvg),
        pipe::get_var(prev) >>= pipe::transform(_subValue(movingAvg)) >>= sink::set_var(diff),
        pipe::get_var(movingAvg) >>= pipe::transform(_subValue(prev)) >>= sink::set_var(diff)
      )
      ,
      sink::set_var(prev)
    )
  )
  >>= pipe::get_var(diff)
  >>= pipe::transform(_greater_than(0.5))
  >>= sink::sum(ssum); // FOr TESTING PURPUSS
  */

 	gen::file<double>(stdin)
	>>= pipe::tee(pipe::fork(
		pipe::partition(_outside(14, 30),
			sink::hole(), 
			restricted_avg<double, 4>(0.5,1)
			>>= sink::set_var(movingAvg)),
		pipe::get_var(prev)
		>>= pipe::partition(_greater_than(movingAvg),
			pipe::get_var(prev)
			>>= pipe::transform(_subValue(movingAvg))
			>>= sink::set_var(diff), 
			pipe::get_var(movingAvg)
			>>= pipe::transform(_subValue(prev))
			>>= sink::set_var(diff)),
		sink::set_var(prev)))
	>>= pipe::get_var(diff)
	>>= pipe::transform(_greater_than(0.5))
	>>= sink::sum(ssum);
  
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start).count();
  printf("Took: %lld\n", duration);
  printf("ssum: %lld, count: %lld\n", ssum, count);
}
//should be: ssum: 99487, count: 100000
