# High level library for creating data flows on low power IoT devices
## DFL
DFL - Data Flow Library is a library for creating a pipeline in C++.  
It comes with generators, pipes and sinks to aid in the creation of a data flow pipeline from the sensor on an IoT device.  

[Documentation](https://oyalmli.github.io/data_flow_library/)  
[Sample Project](https://github.com/Oyalmli/dfl_sample_project)

Example of a simple pipeline:
```cpp
#include "dfl/dfl.hpp"

using namespace dfl;

int main() {
    auto range_gen  = gen::range(0, 42);
    auto pipeline   = pipe::transform([](auto i){return i - 42; });
    auto sink       = sink::for_each([](auto i){ printf("%d\n", i); });

    range_gen >>= pipeline >>= sink;
}
```

DFL also comes with the tools to be able to create your own generators and pipes.  
For creating a generator the user only has to:  
* Inherit dfl::gen::base_generator<CLASS_TYPE, RETURN TYPE>
* Use macro IT(CLASS_TYPE, RETURN_TYPE);
* Implement:
  - hasNext() *-tell the iterator if more values exist*
  - next()    *-next() returns the generators next value*
  - curr()    *-the current value held by the generator*

For creating a pipe the user has to:
* Inherit dfl::dfl_base
* Implement:
  - void onRecieve() *function is called by the pipes library under the hood* **Made by Jonathan Boccara**

Example of creating a generator and a pipe:
```cpp
#include <chrono>
#include <thread>

#include "dfl/dfl.hpp"


/**************** CREATING A GENERATOR ***************/
class sensor_generator 
  : public dfl::gen::base_generator<sensor_generator, int> {

  int _curr;
  pin_t _sensor_pin;
  public:
  sensor_generator(pin_t sensor_pin) : _sensor_pin{sensor_pin} {
    _curr = sensor_read(sensor_pin);
  };
  IT(sensor_generator, int);

  bool hasNext(){ return true; }
  int curr() {return _curr; }
  int next() {
    _curr = sensor_read(_sensor_pin);
    return _curr;
  };

};
/*****************************************************/

/****************** CREATING A PIPE ******************/
template<typename duration_t>
class sleep_pipe 
  : public dfl_base {

  duration_t _sleep_duration;

 public:
  template <typename... Values, typename TailPipeline>
  void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
    //Sends the value/values to the tailPipeline using std::forward
    send(FWD(values)..., tailPipeline);
    std::this_thread::sleep_for(_sleep_duration);
  }

  sleep_pipe(duration_t sleep_duration) 
    : _sleep_duration{sleep_duration} {}

};
/*****************************************************/

int main() {
    Adj_state adjust_state = { alpha = 0.03, phi = 0.01 };
    MaxMin_state maxMin_state = { INT32_MIN, INT32_MAX };
    pin_t sensor_pin = 2;
    auto sensor_gen = sensor_generator(sensor_pin);
    auto idx_gen = gen::counter<long long>();
    
    auto sensor_idx_gen = gen::mux(sine_gen, count_gen);

    sensor_idx_gen
    >>= sleep_pipe(std::chrono::milliseconds(500))
    >>= pipe::set_state(set_min_max, maxMin_state)
    >>= pipe::transform_t(adjust_with_state, adjust_state)
    >>= sink::send_with_mqtt();
}
```
