# High level library for creating data flows on low power IoT devices
## DFL
DFL - Data Flow Library is a library for creating a pipeline in C++.  
It comes with generators, pipes and sinks to aid in the creation of a data flow pipeline from the sensor on an IoT device.  

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
For creating a pipe the user only has to:  
* Inherit dfl::gen::base_generator<CLASS_TYPE, RETURN TYPE>
* Use macro IT(CLASS_TYPE, RETURN_TYPE);
* Implement:
    - hasNext() *-tell the iterator if more values exist*
    - next()    *-next() returns the generators next value*
    - curr()    *-the current value held by the generator*


Example of creating a generator and a pipe:
```cpp
//CREATING A GENERATOR
class sensor_generator : public dfl::gen::base_generator<sensor_generator, int> {
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

//CREATING A PIPE


int main() {
    Adj_state adjust_state = { alpha = 0.03, phi = 0.01 };
    pin_t sensor_pin = 2;
    auto sensor_gen = sensor_generator(sensor_pin);
    
    sensor_gen
    >>= pipe::transform_t(adjust_with_state, adjust_state)
    >>= sink::send_with_mqtt();
}
```
