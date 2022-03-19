#ifndef DVFW_GENERATOR_HPP
#define DVFW_GENERATOR_HPP

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "reader/reader.hpp"

namespace dvfw {
namespace gen {
template <typename T>
class base_generator {
   public:
    bool hasNext();
    T next();

    void wait(int delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    template <typename Pipeline>
    void operator>>=(Pipeline&& pipeline) {
        while (hasNext()) {
            dvfw::send(next(), pipeline);
        }
    }
};

template <typename T>
class file : public base_generator<T> {
   private:
    Reader _reader;

   public:
    file() : _reader{stdin} {};
    file(FILE* f) : _reader{f} {};

    T next() {
        return _reader.next<T>();
    }

    bool hasNext() {
        return _reader.hasNext();
    }

    template <typename Pipeline>
    void operator>>=(Pipeline&& pipeline) {
        while (hasNext()) {
            dvfw::send(next(), pipeline);
                }
    }
};

template <typename T>
class value : public base_generator<T> {
   private:
    T _value;

   public:
    value(T value) : _value{value} {};

    bool hasNext() { return true; }

    T next() {
        return _value;
    }

    template <typename Pipeline>
    void operator>>=(Pipeline&& pipeline) {
        while (hasNext()) {
            dvfw::send(next(), pipeline);
        }
    }
};

template <typename T>
class range : public base_generator<T> {
   private:
    T _min, _max, _step, _curr;

   public:
    range() = default;
    range(T max) : _min{0}, _max{max}, _step{1}, _curr{0} {};
    range(T min, T max) : _min{min}, _max{max}, _step{1}, _curr{min} {};
    range(T min, T max, T step) : _min{min}, _max{max}, _step{step}, _curr{min} {};

    bool hasNext() {
        return _max > _curr;
    }

    T next() {
        T temp = _curr;
        _curr += _step;
        return temp;
    }

    template <typename Pipeline>
    void operator>>=(Pipeline&& pipeline) {
        while (hasNext()) {
            dvfw::send(next(), pipeline);
        }
    }
};

template <class base_generator, typename T>
class noise : public base_generator {
   private:
    base_generator _gen;
    T _noise;

   public:
    noise() = default;
    noise(base_generator generator, T noise, int seed = time(0)) : _gen{generator}, _noise{noise} {
        srand(static_cast<unsigned>(seed));
    }
    float r() {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    bool hasNext() {
        return _gen.hasNext();
    }

    T next() {
        T offset = -_noise + (r() * 2 * _noise);
        return _gen.next() + offset;
    }
};

template <class base_generator, typename T>
class random_err : public base_generator {
    base_generator _gen;
    float _chance;
    T _err;

   public:
    random_err() = default;
    random_err(base_generator generator, float chance, T err, int seed = time(0)) : _gen{generator}, _chance{chance}, _err{err} {
        srand(static_cast<unsigned>(seed));
    }

    float r() {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    bool hasNext() {
        return _gen.hasNext();
    }

    T next() {
        T curr = _gen.next();
        return (_chance > r()) ? _err : curr;
    }
};

};  // namespace gen

template <typename Value, typename Pipeline>
struct generator_pipeline {
    Pipeline pipeline_;
    explicit generator_pipeline(Pipeline& pipeline) : pipeline_(pipeline) {}
};

template <typename Value>
struct generator {};

template <typename Value, typename Pipeline>
auto operator>>=(generator<Value>, Pipeline&& pipeline) {
    return generator_pipeline<Value, std::decay_t<Pipeline>>{pipeline};
}

template <typename Value, typename Pipeline>
void operator>>=(dvfw::gen::base_generator<Value> bg, generator_pipeline<Value, Pipeline> generatorPipeline) {
    while (bg.hasNext()) {
        dvfw::send(bg.next(), generatorPipeline.pipeline_);
    }
}

};  // namespace dvfw

#endif /* DVFW_GENERATOR_HPP */