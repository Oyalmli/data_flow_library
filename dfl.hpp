/**
 * @file dfl.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Entry point for the library
 * 
 * Select which parts of the framework are to be exported
 * 
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DFL_HPP
#define DFL_HPP

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

/**
 * @file base_generator.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief abstract base class for the generators
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DFL_GENERATOR_HPP
#define DFL_GENERATOR_HPP

#include <iterator>

#define MAKE_ITER(CLASS, TP)                                 \
  const CLASS& begin() const { return *this; }               \
  const CLASS& end() const { return *this; }                 \
  bool operator!=(const CLASS&) const { return hasNext(); }  \
  bool operator==(const CLASS&) const { return !hasNext(); } \
  CLASS& operator++() {                                      \
    next();                                                  \
    return *this;                                            \
  }                                                          \
  TP operator*() const { return curr(); }

namespace dfl::gen {
template <typename Gen, typename T>
class GenIterator
    : public std::iterator<std::input_iterator_tag, T, bool, T*, T&> {
  Gen const* _gen;

 public:
  GenIterator(Gen const* gen) : _gen{gen} {};

  void operator++() { _gen->next(); }
  bool operator!=(const GenIterator&) const { return _gen->hasNext(); }
  bool operator==(const GenIterator&) const { return !(_gen->hasNext()); }
  T operator*() const { return _gen->curr(); }
};

template <typename T>
struct base_generator {
  struct iterator {
    typedef T                        value_type;
    typedef bool                     difference_type;
    typedef T*                       pointer;
    typedef T&                       reference;
    typedef std::input_iterator_tag  iterator_category;
  };

  using iterator_category = std::input_iterator_tag;
  using difference_type   = bool;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;

  bool hasNext() const;
  T curr() const;
  void next();
};
}  // namespace dfl::gen

#endif /* DFL_GENERATOR_HPP */

/**
 * @file adjacent.hpp
 * @author Jonathan Boccara
 * @brief Adjacent generator class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example gen/adjacent.cpp
 */
#ifndef DFL_ADJACENT_HPP
#define DFL_ADJACENT_HPP

#include <iterator>

#ifndef DFL_CONCEPTS_HPP
#define DFL_CONCEPTS_HPP

#include <type_traits>

#ifndef DFL_OUTPUT_ITERATOR_HPP
#define DFL_OUTPUT_ITERATOR_HPP

#include <iterator>

#ifndef DFL_FWD_HPP
#define DFL_FWD_HPP

#define FWD(value) std::forward<decltype(value)>(value)

#endif /* DFL_FWD_HPP */
#ifndef DFL_CRTP_HPP
#define DFL_CRTP_HPP

namespace dfl::detail {

template <typename T, template <typename> class crtpType>
struct crtp {
  T& derived() { return static_cast<T&>(*this); }
  T const& derived() const { return static_cast<T const&>(*this); }

 private:
  crtp() {}
  friend crtpType<T>;
};

}  // namespace dfl::detail

#endif /* DFL_CRTP_HPP */
#ifndef DFL_ASSIGNABLE_HPP
#define DFL_ASSIGNABLE_HPP

#include <functional>

#ifndef DFL_OPTIONAL_HPP
#define DFL_OPTIONAL_HPP

#include <optional>

namespace dfl::detail {
using nullopt_t = std::nullopt_t;
static const nullopt_t nullopt = std::nullopt;

template <typename T>
using optional = std::optional<T>;

}  // namespace dfl::detail

#endif /* DFL_OPTIONAL_HPP */

namespace dfl::detail {

template <typename T>
class assignable {
 public:
  assignable& operator=(assignable const& other) {
    value_.emplace(*other.value_);
    return *this;
  }
  assignable& operator=(assignable&& other) {
    value_ = std::move(other.value_);
    return *this;
  }
  assignable(assignable const& other) : value_(other.value_) {}

  assignable(assignable&& other) : value_(std::move(other.value_)) {}

  assignable(T const& value) : value_(value) {}
  assignable(T&& value) : value_(std::move(value)) {}

  T const& get() const { return *value_; }
  T& get() { return *value_; }

  template <typename... Args>
  decltype(auto) operator()(Args&&... args) {
    return (*value_)(std::forward<Args>(args)...);
  }

 private:
  optional<T> value_;
};

template <typename T>
class assignable<T&> {
 public:
  assignable(T& value) : value_(value) {}

  T& get() const { return value_; }
  T& get() { return value_; }

  template <typename... Args>
  decltype(auto) operator()(Args&&... args) {
    return value_(std::forward<Args>(args)...);
  }

 private:
  std::reference_wrapper<T> value_;
};

}  // namespace dfl::detail

#endif /* DFL_ASSIGNABLE_HPP */
#ifndef DFL_SEND_HPP
#define DFL_SEND_HPP

#include <tuple>

namespace dfl {
namespace detail {
template <std::size_t>
struct send_tag {};

template <typename Pipeline, typename... Ts>
void send(send_tag<1>, Pipeline& pipeline, Ts&&... values) {
    pipeline.onReceive(FWD(values)...);
}

template <typename... ValuesThenPipeline, std::size_t... ValuesIndexes>
void send(send_tag<0>, std::tuple<ValuesThenPipeline...> valuesThenPipeline, std::index_sequence<ValuesIndexes...>) {
    auto constexpr pipelineIndex = sizeof...(ValuesThenPipeline) - 1;
    send(send_tag<1>{}, std::get<pipelineIndex>(valuesThenPipeline), std::get<ValuesIndexes>(valuesThenPipeline)...);
}
}  // namespace detail

template <typename T, typename Pipeline>
void send(T&& value, Pipeline& pipeline) {
    pipeline.onReceive(FWD(value));
}

// usage: send(0, 1, 2, 3, myPipeline);
template <typename... ValuesThenPipeline>
void send(ValuesThenPipeline&&... valuesThenPipeline) {
    detail::send(detail::send_tag<0>{}, std::forward_as_tuple(FWD(valuesThenPipeline)...), std::make_index_sequence<sizeof...(ValuesThenPipeline) - 1>{});
}

namespace detail {
template <typename... Ts, typename Pipeline, std::size_t... Is>
void sendTupleValues(std::tuple<Ts...> const& tuple, Pipeline& pipeline, std::index_sequence<Is...>) {
    send(std::get<Is>(tuple)..., pipeline);
}
}  // namespace detail

template <typename... Ts, typename Pipeline>
void sendTupleValues(std::tuple<Ts...> const& tuple, Pipeline& pipeline) {
    detail::sendTupleValues(tuple, pipeline, std::make_index_sequence<sizeof...(Ts)>{});
}
}  // namespace dfl

#endif /* DFL_SEND_HPP */

namespace dfl {
struct dfl_base {};

template <typename Pipeline>
struct pipeline_proxy {
    template <typename T>
    pipeline_proxy& operator=(T&& input) {
        send(FWD(input), pipeline_);
        return *this;
    }

    explicit pipeline_proxy(Pipeline& pipeline) : pipeline_(pipeline) {}

   private:
    Pipeline& pipeline_;
};

template <typename Derived>
struct pipeline_base : detail::crtp<Derived, pipeline_base> {
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    Derived& operator++() { return this->derived(); }
    Derived& operator++(int) {
        ++this->derived();
        return this->derived();
    }
    pipeline_proxy<Derived> operator*() { return pipeline_proxy<Derived>(this->derived()); }
};
}  // namespace dfl

#endif /* DFL_OUTPUT_ITERATOR_HPP */

#ifndef DETECT_HPP
#define DETECT_HPP

#include <type_traits>

namespace dfl::detail {

template <typename...>
using try_to_instantiate = void;

using disregard_this = void;

template <template <typename...> class Expression, typename Attempt,
          typename... Ts>
struct is_detected_impl : std::false_type {};

template <template <typename...> class Expression, typename... Ts>
struct is_detected_impl<Expression, try_to_instantiate<Expression<Ts...>>,
                        Ts...> : std::true_type {};

template <template <typename...> class Expression, typename... Ts>
constexpr bool is_detected =
    is_detected_impl<Expression, disregard_this, Ts...>::value;

}  // namespace dfl::detail

#endif /* DETECT_HPP */

namespace dfl {
namespace detail {
namespace impl {
// definition of range

namespace adl {
using std::begin;
using std::end;
template <typename T>
using begin_expression = decltype(begin(std::declval<T&>()));
template <typename T>
using end_expression = decltype(end(std::declval<T&>()));
}  // namespace adl

template <typename Range>
constexpr bool range_expression_detected = detail::is_detected<adl::begin_expression, Range>&& detail::is_detected<adl::end_expression, Range>;

template <typename Range>
using IsARange = std::enable_if_t<range_expression_detected<Range>, bool>;

// definition of pipe

template <typename Pipe>
using IsAPipe = std::enable_if_t<std::is_base_of<dfl_base, Pipe>::value, bool>;

// definition of pipeline

template <typename Pipeline>
using IsAPipeline = std::enable_if_t<std::is_base_of<pipeline_base<Pipeline>, Pipeline>::value, bool>;
}  // namespace impl

template <typename Range>
using IsARange = impl::IsARange<std::remove_reference_t<Range>>;

template <typename Pipe>
using IsAPipe = impl::IsAPipe<std::remove_reference_t<Pipe>>;

template <typename Pipeline>
using IsAPipeline = impl::IsAPipeline<std::remove_reference_t<Pipeline>>;

}  // namespace detail
}  // namespace dfl

#endif /* DFL_CONCEPTS_HPP */

namespace dfl::gen {
template <typename Range>
struct adjacent_range {
  const Range& range;
  explicit adjacent_range(Range const& range) : range(range) {}
};

/**
 * @brief Generator sending pairs of values
 *
 * @tparam Range
 * @param range
 * @return auto
 */
template <typename Range>
auto adjacent(Range&& range) {
  return adjacent_range<Range>(FWD(range));
}

template <typename Range, typename Pipeline,
          detail::IsAPipeline<Pipeline> = true>
void operator>>=(adjacent_range<Range> rangesHolder, Pipeline&& pipeline) {
  auto range = rangesHolder.range;
  auto it = range.begin();
  auto end = range.end();

  if (it == end) {
    return;
  }

  auto a = *it;
  if (it == end) return;
  ++it;
  auto b = *it;
  while (it != end) {
    send(a, b, pipeline);
    a = b;
    ++it;
    b = *it;
  }
}
}  // namespace dfl::gen

#endif /* DFL_ADJACENT_HPP */
/**
 * @file counter.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Counter generator class
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * @example gen/counter.cpp
 */

#ifndef GEN_COUNTER_HPP
#define GEN_COUNTER_HPP

namespace dfl::gen {
template <typename T>
class counter : public base_generator<T> {
  T _curr;

 public:
  /**
   * @brief Counts from 0
   * 
   * @param max 
   */
  counter() : _curr{0} {}
  bool hasNext() const { return true; }
  T curr() const { return _curr; }
  void next() { _curr++; }

  MAKE_ITER(counter, T);
};
} // namespace dfl::gen

#endif //GEN_COUNTER_HPP
/**
 * @file file.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief File generator class
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 * @example gen/file.cpp
 */
#ifndef GEN_FILE_HPP
#define GEN_FILE_HPP

/**
 * @file IO.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Utility class for very fast buffered reading and writing
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef IO_HPP
#define IO_HPP

#include <string>
#define MORE ++

template<size_t BUFFER_SIZE>
class Writer {
   private:
    bool _alert_mode = false;
    FILE* _fp_o = stderr;
    FILE* _fp;

    uint8_t buffer[BUFFER_SIZE];
    uint_fast32_t bufferPointer = 0;

    void _flushBuffer() {
        fwrite(buffer, 1, bufferPointer, _fp);
        bufferPointer = 0;
    }

    constexpr void _write(uint8_t c) {
        buffer[bufferPointer++] = c;
        if (bufferPointer >= BUFFER_SIZE) {
            _flushBuffer();
        }
    }

    void _writeStr(const char* str, size_t N) {
        for (int i = 0; i < N; ++i) {
            _write(str[i]);
        }
    }

   public:
    Writer(FILE* outputStream = stdout) : _fp{outputStream} {}

    ~Writer() {
        fclose(_fp);
    }

    void flush() {
        _flushBuffer();
    }

    void write(std::string& s) {
        _writeStr(s.c_str(), s.size());
    }

    template <typename T>
    void write(T val) {
        if constexpr (std::is_same_v<T, char>) {
            _write(val);
            return;
        } else
        if constexpr (std::is_same_v<T, const char*>) {
            _writeStr(val, strlen(val));
            return;
        } else
        if constexpr (std::is_same_v<T, std::string>) {
            _writeStr(val.c_str(), val.size());
            return;
        } else
        if constexpr (true) {
            std::string s = std::to_string(val);
            _writeStr(s.c_str(), s.size());
        } 
    }

    template <typename T>
    Writer& operator<(T val) {
        write(val);
        return *this;
    }

    Writer& alertMode(){
        if(_alert_mode){
            _flushBuffer();
            _alert_mode = false;
            std::swap(_fp, _fp_o);
        } else {
            _alert_mode = true;
            std::swap(_fp, _fp_o);
        }
        return *this;
    }
};

template<size_t BUFFER_SIZE>
class Reader {
   private:
    FILE* _fp;
    
    uint8_t buffer[BUFFER_SIZE];
    uint_fast32_t bufferPointer = 0, bytesRead = 0;

    bool _fillBuffer() {
        #ifdef __linux__
            bytesRead = fread_unlocked(buffer, 1, BUFFER_SIZE, _fp);
        #else 
            bytesRead = fread(buffer, 1, BUFFER_SIZE, _fp);
        #endif
        bufferPointer = 0;
        return bytesRead;
    }

    constexpr uint8_t _read() {
        if (!hasNext()) return '\0';
        return buffer[bufferPointer++];
    }

    template <typename T>
    constexpr T _readUnsignedInteger() {
        T ret = 0;
        uint8_t c = _read();
        for (; (c < '0' || c > '9') && c != '\0'; c = _read());
        for (; c >= '0' && c <= '9'; c = _read()) {
            ret = ret * 10 + (c - '0');
        }
        return ret;
    }

    template <typename T>
    constexpr T _readInteger() {
        T ret = 0;
        bool neg = false;
        uint8_t c = _read();
        for (; (c < '0' || c > '9') && c != '\0'; c = _read()) {
            neg = (c == '-');
        }
        for (; c >= '0' && c <= '9'; c = _read()) {
            ret = ret * 10 + (c - '0');
        }
        return neg ? -ret : ret;
    }

    template <typename T>
    constexpr T _readFloating() {
        T pow10 = 1, left = 0, right = 0;
        bool neg = false;
        uint8_t c = _read();
        for (; (c < '0' || c > '9') && c != '\0'; c = _read()) {
            neg = (c == '-');
        }
        for (; c >= '0' && c <= '9'; c = _read()) {
            left = left * 10 + (c - '0');
        }
        if (c == '.') {
            for (c = _read(); c >= '0' && c <= '9'; c = _read()) {
                right = right * 10 + (c - '0');
                pow10 *= 10;
            }
            left += right /= pow10;
        }
        return neg ? -left : left;
    }

    std::string _readWord() {
        std::string res;
        uint8_t c = _read();
        for (; std::isspace(c) && c != '\0'; c = _read())
            ;
        for (; !std::isspace(c) && c != '\0'; c = _read()) {
            res.push_back(c);
        }
        return res;
    }

    std::string _readLine() {
        std::string res;
        for (uint8_t c = _read(); c != '\n' && c != '\0'; c = _read()) {
            res.push_back(c);
        }
        return res;
    }

   public:
    Reader(FILE* inputStream = stdin) : _fp{inputStream} {}

    ~Reader() {
        fclose(_fp);
    }

    std::string getWord() { return _readWord(); }
    std::string getLine() { return _readLine(); }

    constexpr uint8_t getChar() {
        return _read();
    }

    constexpr bool hasNext() {
        return (bufferPointer < bytesRead) || _fillBuffer();
    }

    void skipToken() {
        uint8_t c = _read();
        for (; std::isspace(c) && c != '\0'; c = _read());
        for (; !std::isspace(c); c = _read());
    }

    template <typename T, bool word = true>
    constexpr T next() {
        if constexpr (std::is_same_v<T, std::string>){
            if constexpr(word) return _readWord();
            return _readLine();
        }
        if constexpr (std::is_same_v<T, char>){
            return _read();
        }
        if constexpr ( std::is_unsigned<T>::value && std::is_integral<T>::value ) { 
            return _readUnsignedInteger<T>();
        }
        if constexpr ( std::is_integral<T>::value ) { 
            return _readInteger<T>(); 
        }
        if constexpr ( std::is_floating_point<T>::value ) { 
            return _readFloating<T>(); 
        }
    }

    template <typename T, class... Args>
    constexpr void set(T *x, Args... args){
        *x = next<T>();
        if constexpr (sizeof...(Args) > 0) {
            set(args...);
        }
    }
};

template <size_t R_BUF = 128, size_t W_BUF = R_BUF>
class IO {
   public:
    Writer<R_BUF> writer;
    Reader<W_BUF> reader;

    IO (FILE* read_path = stdin, FILE* write_path = stdout) 
        : reader{read_path}, writer{write_path} {}

    /**
     * @brief Add the value to the writeStream
     * 
     * @tparam T 
     * @param val 
     * @return constexpr IO& 
     */
    template <typename T>
    constexpr IO& operator<<(T val) {
        writer.write(val);
        return *this;
    }

    /**
     * @brief Set the value to the next value
     * 
     * @tparam T 
     * @param val 
     * @return constexpr IO& 
     */
    template <typename T>
    constexpr IO& operator>>(T& val) {
        val = reader.template next<T, true>();
        return *this;
    }

    /**
     * @brief Adds the next value from the value provided
     * * EXAMPLE:
     * int i = 10;
     * io - i;  //io returns 8
     * io << i; //prints 18
     * 
     * @tparam T 
     * @param val 
     * @return constexpr IO& 
     */
    template <typename T>
    constexpr IO& operator+(T& val) {
        val += reader.template next<T, true>();
        return *this;
    }

    /**
     * @brief Subtracts the next value from the value provided
     * EXAMPLE:
     * int i = 10;
     * io - i;  //io returns 8
     * io << i; //prints 2
     * 
     * @tparam T 
     * @param val 
     * @return constexpr IO& 
     */
    template <typename T>
    constexpr IO& operator-(T& val) {
        val -= reader.template next<T, true>();
        return *this;
    }

    /**
     * @brief Check if the inputstream has not reached its end
     * EXAMPLE:
     * int i;
     * while(MORE io){
     *   io >> i;
     *   io << i << '\n';
     * }
     * 
     * @return MORE
     */
    constexpr bool operator MORE() {
        return reader.hasNext();
    }

    /**
     * @brief Toggle alert mode [stdout | stderr]
     * EXAMPLE:
     * int meaningOfLife = 42;
     * !io << "hello" << meaningOfLife << '\n' << !io;
     * 
     * Should be used at the start and end of the line to make sure to flush what was in the buffer
     * As well as returning to stdout
     * @return constexpr IO& 
     */
    constexpr IO& operator!() {
        writer.alertMode();
        return *this;
    }
};

#endif

namespace dfl::gen {
template <typename T, bool word = true, size_t BUF_SIZE=128>
class file : public base_generator<T> {
 private:
  Reader<BUF_SIZE> _reader;
  int more = 1;
  T _curr;

 public:
  /**
   * @brief Construct a new file object
   *
   * @param f FILE*
   */
  file(FILE* f = stdin) : _reader{f} { next(); };
  file(const char* file_path) : _reader{fopen(file_path, "r")} { next(); };

  bool hasNext() const {
    return more > -1;
  }

  T curr() const { return _curr; }

  void next() {
    _curr = _reader.template next<T, word>();
    more += _reader.hasNext() -1;
  }

  MAKE_ITER(file, T);
};
}  // namespace dfl::gen

#endif  // GEN_FILE_HPP
/**
 * @file noise.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Noise generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/noise.cpp
 */
#ifndef GEN_MOD_NOISE_HPP
#define GEN_MOD_NOISE_HPP

namespace dfl::mod {
template <class Gen>
class noise : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen;
  T _noise;
  T _curr = _gen.curr();

  double r() { return rand() / static_cast<double>(RAND_MAX); }

 public:
  /**
   * @brief Default noise constructor
   * @warning Do not use
   */
  noise() = default;
  /**
   * @brief Modifies the values supplied by the generator with a set noise range
   *
   * @param noise
   * @param generator
   * @param seed
   */
  noise(T noise, Gen generator, int seed = time(0))
      : _gen{generator}, _noise{noise} {
    srand(static_cast<unsigned>(seed));
  }

  bool hasNext() const { return _gen.hasNext(); }
  T curr() const { return _curr; }
  void next() {
    T offset = -_noise + (r() * 2 * _noise);
    _gen.next();
    _curr = _gen.curr() + offset;
  }

  MAKE_ITER(noise, T);
};
}  // namespace dfl::gen

#endif  // GEN_MOD_NOISE_HPP

/**
 * @file random_err.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Random Error generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/random_err.cpp
 */
#ifndef GEN_MOD_RANDOM_ERR_HPP
#define GEN_MOD_RANDOM_ERR_HPP

namespace dfl::mod {
template <class Gen>
class random_err : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen;
  double _chance;
  T _err;
  T _curr = _gen.curr();

 public:
  /**
   * @brief Has a set chance to insert a set error value
   *
   * @param chance
   * @param err
   * @param generator
   * @param seed
   */
  random_err(double chance, T err, Gen generator, int seed = time(0))
      : _gen{generator}, _chance{chance}, _err{err} {
    srand(static_cast<unsigned>(seed));
  }

  double r() {
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
  }

  bool hasNext() const { return _gen.hasNext(); }
  T curr() const { return _curr; }

  void next() {
    _gen.next();
    T curr = _gen.curr();
    _curr = (_chance > r()) ? _err : curr;
  }

  MAKE_ITER(random_err, T);  
};
}  // namespace dfl::gen

#endif  // GEN_MOD_RANDOM_ERR_HPP

/**
 * @file take.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Take generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/take.cpp
 */
#ifndef GEN_MOD_TAKE_HPP
#define GEN_MOD_TAKE_HPP

namespace dfl::mod {
template <class Gen>
class take : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;
  //using iterator = GenIterator<take<Gen>, T>;

 private:
  Gen _gen;
  size_t _num;
  size_t _taken{0};
  T _curr = _gen.curr();

 public:
  take(size_t num, const Gen generator) : _gen{generator}, _num{num} {}

  bool hasNext() const { return _gen.hasNext() && (_taken < _num); }
  T curr() const { return _curr; }

  void next() {
    _taken++;
    _gen.next();
    _curr = _gen.curr();
  }
  
  MAKE_ITER(take, T);
};
}  // namespace dfl::gen

#endif  // GEN_MOD_TAKE_HPP

/**
 * @file repeat.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Repeat generator modifyier class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example mod/repeat.cpp
 */
#ifndef GEN_MOD_REPEAT_HPP
#define GEN_MOD_REPEAT_HPP

namespace dfl::mod {
template <class Gen>
class repeat : public gen::base_generator<typename Gen::value_type> {
  using T = typename Gen::value_type;

 private:
  Gen _gen_init;
  Gen _gen;

 public:
  T _curr = _gen.curr();

  repeat(Gen generator) : _gen_init{generator}, _gen{generator} {}

  bool hasNext() const { return true; }
  T curr() const { return _curr; }

  void next() {
    _gen.next();
    if (!_gen.hasNext()) {
      _gen = _gen_init;
    }
    _curr = _gen.curr();
  }
  MAKE_ITER(repeat, T);
};
}  // namespace dfl::gen

#endif  // GEN_MOD_REPEAT_HPP

/**
 * @file range.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Range generator class
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 * @example gen/range.cpp
 */
#ifndef DFL_GEN_RANGE_HPP
#define DFL_GEN_RANGE_HPP

namespace dfl::gen {
template <typename T>
class range : public base_generator<T> {

 private:
  T _min, _max, _step, _curr;

 public:

  /**
   * @brief Construct a range generator
   *
   */

  constexpr range(T max=0) 
    : _min{0}, _max(max), _step(1), _curr(0) 
    {};
  constexpr range(T min, T max, T step=1)
    : _min(min), _max(max), _step(step), _curr(min) 
    {};
  
  bool hasNext() const { return _max > _curr; };
  T curr() const { return _curr; }
  void next() { _curr += _step; }
  MAKE_ITER(range, T);
};
}  // namespace dfl::gen

#endif  // DFL_GEN_RANGE_HPP

/**
 * @file sine.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Sine generator class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example gen/sine.cpp
 */
#ifndef GEN_SINE_HPP
#define GEN_SINE_HPP

#include <cmath>

namespace dfl::gen {

template <typename T,
          typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class sine : public base_generator<T> {
 private:
  T _freq, _ampl, _yOffset, _curr;
  long long _cnt = 0;

  double getSine() {
    return (_ampl * sin(2 * M_PI * _freq * (_cnt++) + 0) + _yOffset);
  }

 public:
  /**
   * @brief Creates a sine wave generator with as set frequency, amplitude and
   * offset.
   *
   * @param freq
   * @param ampl
   * @param yOffset
   */
  sine(T freq = 0.0, T ampl = 1.0, T yOffset = 0.0)
      : _freq{freq}, _ampl{ampl}, _yOffset{yOffset} {
    next();
  };

  bool hasNext() const { return true; }
  T curr() const { return _curr; }
  void next() { _curr = getSine();}
  
  MAKE_ITER(sine, T);
};
}  // namespace dfl::gen

#endif  // GEN_SINE_HPP

/**
 * @file value.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Value generator class
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 * @example gen/value.cpp
 */
#ifndef DFL_GEN_VALUE_HPP
#define DFL_GEN_VALUE_HPP

namespace dfl::gen {

template <typename T>
class value : public base_generator<T> {
 private:
  T _curr;

 public:
  /**
   * @brief Repeats the set value
   *
   * @param value to be repeated
   */
  value(T value = 0) : _curr{value} {};

  bool hasNext() const { return true; }
  T curr() const { return _curr; }
  void next() { }
  
  MAKE_ITER(value, T);
};
}  // namespace dfl::gen

#endif

#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <iostream>
#include <type_traits>

#ifndef DFL_PIPES_ASSEMBLY
#define DFL_PIPES_ASSEMBLY

namespace dfl {
namespace detail {

template <typename HeadPipe, typename TailPipeline>
class generic_pipeline : public pipeline_base<generic_pipeline<HeadPipe, TailPipeline>> {
   public:
    template <typename... Ts>
    void onReceive(Ts&&... inputs) {
        headPipe_.template onReceive<Ts...>(FWD(inputs)..., tailPipeline_);
    }

    generic_pipeline(HeadPipe headPipe, TailPipeline tailPipeline) : headPipe_(headPipe), tailPipeline_(tailPipeline) {}

   private:
    HeadPipe headPipe_;
    TailPipeline tailPipeline_;
};

template <typename Pipe1, typename Pipe2>
struct CompositePipe : public dfl_base {
    Pipe1 pipe1;
    Pipe2 pipe2;

    template <typename Pipe1_, typename Pipe2_>
    CompositePipe(Pipe1_&& pipe1, Pipe2_&& pipe2) : pipe1(FWD(pipe1)), pipe2(FWD(pipe2)) {}
};

template <typename HeadPipe, typename TailPipeline>
auto make_generic_pipeline(HeadPipe&& headPipe, TailPipeline&& tailPipeline) {
    return generic_pipeline<std::decay_t<HeadPipe>, std::decay_t<TailPipeline>>{FWD(headPipe), FWD(tailPipeline)};
}

template <typename Pipe1, typename Pipe2, typename TailPipeline>
auto make_generic_pipeline(detail::CompositePipe<Pipe1, Pipe2> compositePipe, TailPipeline&& tailPipeline) {
    return make_generic_pipeline(compositePipe.pipe1, make_generic_pipeline(compositePipe.pipe2, tailPipeline));
}

}  // namespace detail
}  // namespace dfl

#endif /* DFL_PIPES_ASSEMBLY */

namespace dfl {
// range >>= pipeline (rvalue ranges)

template <typename Range, typename Pipeline, detail::IsARange<Range> = true,
          detail::IsAPipeline<Pipeline> = true>
std::enable_if_t<!std::is_lvalue_reference<Range>::value> operator>>=(
    Range&& range, Pipeline&& pipeline) {
  for (const auto i : range) send(i, pipeline);
}

// range >>= pipeline (lvalue ranges)

template <typename Range, typename Pipeline, detail::IsARange<Range> = true,
          detail::IsAPipeline<Pipeline> = true>
std::enable_if_t<std::is_lvalue_reference<Range>::value> operator>>=(
    Range&& range, Pipeline&& pipeline) {
  for (const auto i : range) send(i, pipeline);
}

// pipe >>= pipe

template <typename Pipe1, typename Pipe2, detail::IsAPipe<Pipe1> = true,
          detail::IsAPipe<Pipe2> = true>
auto operator>>=(Pipe1&& pipe1, Pipe2&& pipe2) {
  return detail::CompositePipe<std::decay_t<Pipe1>, std::decay_t<Pipe2>>(
      FWD(pipe1), FWD(pipe2));
}

// pipe >>= pipeline

template <typename Pipe, typename Pipeline, detail::IsAPipe<Pipe> = true,
          detail::IsAPipeline<Pipeline> = true>
auto operator>>=(Pipe&& pipe, Pipeline&& pipeline) {
  return make_generic_pipeline(pipe, pipeline);
}

}  // namespace dfl

#endif /* OPERATOR_HPP */

/**
 * @file chunks.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Chunk pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/chunks.cpp
 */
#ifndef DFL_CHUNKS_HPP
#define DFL_CHUNKS_HPP

#include <vector>

namespace dfl::pipe {
template <typename T, std::size_t N>
class chunks : public dfl_base {
   public:

   /**
    * @brief Forwards the values supplied to the next pipeline
    * 
    * @tparam Values 
    * @tparam TailPipeline 
    * @param values 
    * @param tailPipeline 
    */
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        _curr_chunk.push_back(values...);
        if (_curr_chunk.size() >= N) {
            send(_curr_chunk, tailPipeline);
            _curr_chunk.clear();
        }
    }

    /**
     * @brief Generates chunks of size N
     */
    explicit chunks() {}

   private:
    std::vector<T> _curr_chunk;
};
}  // namespace dfl::pipe

#endif /* PIPES_CHUNKS_HPP */
/**
 * @file drop.hpp
 * @author Jonathan Boccara
 * @brief Drop generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/drop.cpp
 */
#ifndef DFL_DROP_HPP
#define DFL_DROP_HPP

namespace dfl {
namespace pipe {
class drop : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (nbDropped_ >= nbToDrop_) {
            send(FWD(values)..., tailPipeline);
        } else {
            ++nbDropped_;
        }
    }

    explicit drop(std::size_t nbToDrop) : nbToDrop_{nbToDrop}, nbDropped_{0} {}

   private:
    std::size_t nbToDrop_;
    std::size_t nbDropped_;
};
}  // namespace pipe
}  // namespace dfl

#endif /* PIPES_DROP_HPP */
/**
 * @file drop_while.hpp
 * @author Jonathan Boccara
 * @brief Drop while pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/drop_while.cpp
 */
#ifndef DFL_DROP_WHILE_HPP
#define DFL_DROP_WHILE_HPP

namespace dfl {
namespace pipe {
template <typename Predicate>
class drop_while_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (!predicateHasBeenFalse_) {
            predicateHasBeenFalse_ = !predicate_(values...);
        }

        if (predicateHasBeenFalse_) {
            send(FWD(values)..., FWD(tailPipeline));
        }
    }

    explicit drop_while_pipe(Predicate predicate) : predicate_{predicate}, predicateHasBeenFalse_{false} {}

   private:
    detail::assignable<Predicate> predicate_;
    bool predicateHasBeenFalse_;
};

template <typename Predicate>
drop_while_pipe<Predicate> drop_while(Predicate&& predicate) {
    return drop_while_pipe<Predicate>(FWD(predicate));
}
}  // namespace pipe
}  // namespace dfl

#endif /* DFL_DROP_WHILE_HPP */
/**
 * @file filter.hpp
 * @author Jonathan Boccara
 * @brief Filter pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/filter.cpp
 */
#ifndef DFL_FILTER_HPP
#define DFL_FILTER_HPP

namespace dfl {
namespace pipe {
template <typename Predicate>
class filter_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (predicate_(values...)) {
            send(FWD(values)..., tailPipeline);
        }
    }

    explicit filter_pipe(Predicate predicate) : predicate_(predicate) {}

   private:
    detail::assignable<Predicate> predicate_;
};

template <typename Predicate>
auto filter(Predicate&& predicate) {
    return filter_pipe<std::decay_t<Predicate>>{predicate};
}
}  // namespace pipe
}  // namespace dfl

#endif /* DFL_FILTER_HPP */
/**
 * @file fork.hpp
 * @author Jonathan Boccara
 * @brief Fork pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/fork.cpp
 */
#ifndef DFL_FORK_HPP
#define DFL_FORK_HPP

#ifndef DFL_META_HPP
#define DFL_META_HPP

#include <type_traits>
#include <utility>

namespace dfl::detail {

template <class Tuple, class F, std::size_t... I>
F for_each_impl(Tuple&& t, F&& f, std::index_sequence<I...>) {
  return (void)std::initializer_list<int>{
             (std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))), 0)...},
         f;
}

template <class Tuple1, class Tuple2, class F, std::size_t... I>
F for_each2_impl(Tuple1&& t1, Tuple2&& t2, F&& f, std::index_sequence<I...>) {
  return (void)std::initializer_list<int>{
             (std::forward<F>(f)(std::get<I>(std::forward<Tuple1>(t1)),
                                 std::get<I>(std::forward<Tuple2>(t2))),
              0)...},
         f;
}

template <class F, class Tuple>
constexpr decltype(auto) for_each(Tuple&& t, F&& f) {
  return detail::for_each_impl(
      std::forward<Tuple>(t), std::forward<F>(f),
      std::make_index_sequence<
          std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}

template <class Tuple1, class Tuple2, class F>
constexpr decltype(auto) for_each2(Tuple1&& t1, Tuple2&& t2, F&& f) {
  return detail::for_each2_impl(
      std::forward<Tuple1>(t1), std::forward<Tuple2>(t2), std::forward<F>(f),
      std::make_index_sequence<
          std::tuple_size<std::remove_reference_t<Tuple1>>::value>{});
}

template <typename... Ts, typename Function, size_t... Is>
auto transform_impl(std::tuple<Ts...>const& inputs, Function function,
                    std::index_sequence<Is...>) {
  return std::make_tuple(function(std::get<Is>(inputs))...);
}

template <typename... Ts, typename Function>
auto transform(std::tuple<Ts...>const& inputs, Function function) {
  return transform_impl(inputs, function,
                        std::make_index_sequence<sizeof...(Ts)>{});
}

template <typename Tuple, typename Predicate>
size_t find_if(Tuple&& tuple, Predicate pred) {
  size_t index = std::tuple_size<std::decay_t<Tuple>>::value;
  size_t currentIndex = 0;
  bool found = false;
  for_each(tuple, [&](auto&& value) {
    if (!found && pred(value)) {
      ++index = currentIndex;
      found = true;
    }
    ++currentIndex;
  });
  return index;
}

template <typename Tuple, typename Predicate>
bool any_of(Tuple&& tuple, Predicate pred) {
  return find_if(tuple, pred) != std::tuple_size<std::decay_t<Tuple>>::value;
}

template <typename Tuple, typename Action>
void perform(Tuple&& tuple, size_t index, Action action) {
  size_t currentIndex = 0;
  for_each(tuple,
           [action = std::move(action), index, &currentIndex](auto&& value) {
             if (currentIndex == index) {
               action(std::forward<decltype(value)>(value));
             }
             ++currentIndex;
           });
}

template <typename... Ts>
auto dereference(std::tuple<Ts...> const& tuple) {
  return transform(tuple,
                   [](auto&& element) -> decltype(auto) { return *element; });
}

}  // namespace dfl::detail

#endif /* DFL_META_HPP */

namespace dfl {
namespace pipe {
template <typename... TailPipelines>
class fork_pipeline : public pipeline_base<fork_pipeline<TailPipelines...>> {
   public:
    template <typename... T>
    void onReceive(T&&... values) {
        detail::for_each(tailPipelines_, [&values...](auto&& tailPipeline) { send(FWD(values)..., tailPipeline); });
    }

    /**
     * @brief Forwards the same value to all pipelines defined in it
     * 
     * @param tailPipelines 
     */
    explicit fork_pipeline(TailPipelines const&... tailPipelines) : tailPipelines_(tailPipelines...) {}

   private:
    std::tuple<TailPipelines...> tailPipelines_;
};

template <typename... TailPipelines>
fork_pipeline<TailPipelines...> fork(TailPipelines const&... tailPipelines) {
    return fork_pipeline<TailPipelines...>(tailPipelines...);
}
}  // namespace pipe
}  // namespace dfl

#endif /* DFL_FORK_HPP */
/**
 * @file intersperse.hpp
 * @author Jonathan Boccara
 * @brief Intersperse pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/intersperse.cpp
 */
#ifndef DFL_INTERSPERSE_HPP
#define DFL_INTERSPERSE_HPP

namespace dfl {
namespace pipe {
template <typename Delimiter>
class intersperse_pipe : public dfl_base {
   public:
    template <typename T, typename TailPipeline>
    void onReceive(T&& value, TailPipeline& tailPipeline) {
        if (alreadyReceivedAValue_) {
            send(delimiter_, tailPipeline);
        }
        send(FWD(value), tailPipeline);
        alreadyReceivedAValue_ = true;
    }

    explicit intersperse_pipe(Delimiter delimiter) : delimiter_(std::move(delimiter)) {}

   private:
    Delimiter delimiter_;
    bool alreadyReceivedAValue_ = false;
};
/**
 * @brief Places the delemiter value between each recieved value
 * 
 * @tparam Delimiter 
 * @param delimiter 
 * @return auto 
 */
template <typename Delimiter>
auto intersperse(Delimiter delimiter) {
    return intersperse_pipe<Delimiter>{delimiter};
}
}  // namespace pipe
}  // namespace dfl

#endif /* DFL_INTERSPERSE_HPP */
/**
 * @file moving_avg.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Moving average pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/moving_avg.cpp
 */
#ifndef DFL_MOVING_AVERAGE_HPP
#define DFL_MOVING_AVERAGE_HPP

namespace dfl {
namespace pipe {
template <typename T, std::size_t N>
class moving_avg : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(FWD(get_avg(values...)), tailPipeline);
    }

    /**
     * @brief Returns a moving average of the last N values
     * @return moving average {double}
     */
    explicit moving_avg() : _total{0} {}

   private:
    T _samples[N];
    size_t _num_samples{0};
    T _total;

    double get_avg(T sample) {
        _total += sample;
        if (_num_samples < N)
            _samples[_num_samples++] = sample;
        else {
            T& oldest = _samples[_num_samples++ % N];
            _total -= oldest;
            oldest = sample;
        }
        return _total / static_cast<double>(std::min(_num_samples, N));
    }
};
}  // namespace pipe
}  // namespace dfl

#endif /* DFL_MOVING_AVERAGE_HPP */
/**
 * @file partition.hpp
 * @author Jonathan Boccara
 * @brief Partition pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/partition.cpp
 */
#ifndef DFL_PARTITION_HPP
#define DFL_PARTITION_HPP

namespace dfl::pipe {
template <typename OutputPipeTrue, typename OutputPipeFalse, typename Predicate>
class partition_pipe : public pipeline_base<partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate>> {
   public:
    template <typename... Ts>
    void onReceive(Ts&&... values) {
        if (predicate_(values...)) {
            send(FWD(values)..., outputPipeTrue_);
        } else {
            send(FWD(values)..., outputPipeFalse_);
        }
    }

    explicit partition_pipe(OutputPipeTrue iteratorTrue, OutputPipeFalse iteratorFalse, Predicate predicate) : outputPipeTrue_(iteratorTrue), outputPipeFalse_(iteratorFalse), predicate_(predicate) {}

   private:
    OutputPipeTrue outputPipeTrue_;
    OutputPipeFalse outputPipeFalse_;
    detail::assignable<Predicate> predicate_;
};

/**
 * @brief Given a predicate function a value will be sent to the first pipleine if true the other if not
 * 
 * @tparam Predicate 
 * @tparam OutputPipeTrue 
 * @tparam OutputPipeFalse 
 * @param predicate 
 * @param outputPipeTrue 
 * @param outputPipeFalse 
 * @return partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate> 
 */
template <typename Predicate, typename OutputPipeTrue, typename OutputPipeFalse>
partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate> partition(Predicate predicate, OutputPipeTrue&& outputPipeTrue, OutputPipeFalse&& outputPipeFalse) {
    return partition_pipe<OutputPipeTrue, OutputPipeFalse, Predicate>(FWD(outputPipeTrue), FWD(outputPipeFalse), predicate);
}
}  // namespace dfl::pipe

#endif /* DFL_PARTITION_HPP */
/**
 * @file scanl.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Scanl pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/scanl.cpp 
 */
#ifndef DFL_SCANL_HPP
#define DFL_SCANL_HPP

namespace dfl::pipe {
template <typename Function, typename State>
class scanl_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        state_ = function_(state_, values...);
        send(FWD(state_), tailPipeline);
    }

    explicit scanl_pipe(Function function, State initState) : function_(function), state_(initState) {}

   private:
    Function function_;
    State state_;
};

/**
 * @brief Scanl function for applying funciton with a kept state
 * 
 * Applies a function to every element of a range with the internal state as the first arugment, and the value from the range as the other
 * 
 * @tparam Function 
 * @tparam State 
 * @param function 
 * @param initState 
 * @return scanl_pipe<Function, State> 
 */
template <typename Function, typename State>
scanl_pipe<Function, State> scanl(Function&& function, State initState) {
    return scanl_pipe<Function, State>{function, initState};
}
}  // namespace dfl::pipe

#endif /* DFL_SCANL_HPP */
/**
 * @file set_state.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Set state pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/set_state.cpp
 */
#ifndef DFL_SET_STATE_HPP
#define DFL_SET_STATE_HPP

namespace dfl::pipe {
template <typename Function, typename State>
class set_state_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        state_ = function_(values..., state_);
        send(FWD(values)..., tailPipeline);
    }

    explicit set_state_pipe(Function function, State state) : function_(function), state_(state) {}

   private:
    Function function_;
    State state_;
};

/**
 * @brief Sets the state of the given variable using the function provided
 * 
 * EXAMPLE:
 * int max = 0;
 * auto generator = gen::range(100);
 * auto pipeline 
 * =   pipe::set_state([](auto i, auto& max_){ max_ = i > max_ ? i : max_; }, max)
 * >>= sink::hole();
 * generator >>= pipeline;
 * printf("%d\n", max);

 * @tparam Function 
 * @tparam State 
 * @param function 
 * @param state 
 * @return set_state_pipe<Function, State> 
 */
template <typename Function, typename State>
set_state_pipe<Function, State> set_state(Function&& function, State&& state) {
    return set_state_pipe<Function, State>{function, state};
}
}  // namespace dfl::pipe

#endif /* DFL_SET_STATE_HPP */
/**
 * @file set_state.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Set state pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/set_state.cpp
 */
#ifndef DFL_PIPE_SET_VAR_HPP
#define DFL_PIPE_SET_VAR_HPP

namespace dfl::pipe {
template <typename State>
class set_var_pipe : public dfl_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        state_ = value;
        send(FWD(value), tailPipeline);
    }
    /**
     * @brief Sets the state of the given variable
     * 
     * EXAMPLE:
     * int last = 0;
     * gen::range(100)
     * >>= pipe::set_var(last) >>= sink::hole();
     * printf("%d\n", max);

    * @tparam State 
    * @param state 
    * @return set_var_pipe<State> 
    */
    explicit set_var_pipe(State state) : state_(state) {}

   private:
    State state_;
};
template <typename State>
set_var_pipe<State> set_var(State&& state) {
    return set_var_pipe<State>{state};
}
}  // namespace dfl::pipe

#endif /* DFL_SINK_SET_STATE_HPP */
/**
 * @file side_effect.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Side effect pipeline class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example pipe/side_effect.cpp
 */
#ifndef DFL_SIDE_EFFECT_HPP
#define DFL_SIDE_EFFECT_HPP

namespace dfl::pipe {
template <typename Function>
class side_effect_pipe : public dfl_base {
 public:
  template <typename... Values, typename TailPipeline>
  void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
    function_();
    send(FWD(values)..., tailPipeline);
  }

  explicit side_effect_pipe(Function function) : function_(function) {}

 private:
  detail::assignable<Function> function_;
};
/**
 * @brief Runs a side effect function. The values will be passed on, but the
 * function will be run, taking no arguments.
 *
 * @tparam Function
 * @param function
 * @return transform_pipe<Function>
 */
template <typename Function>
side_effect_pipe<Function> side_effect(Function&& function) {
  return side_effect_pipe<Function>{function};
}
}  // namespace dfl::pipe

#endif /* DFL_SIDE_EFFECT_HPP */
/**
 * @file stride.hpp
 * @author Jonathan Boccara
 * @brief
 * @version 0.1
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 * @example pipe/stride.cpp
 */
#ifndef PIPES_STEP_HPP
#define PIPES_STEP_HPP

namespace dfl::pipe {
class stride : public dfl_base {
 public:
  template <typename... Values, typename TailPipeline>
  void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
    if (nbSinceLastStride_ <= 0) {
      send(FWD(values)..., FWD(tailPipeline));
      nbSinceLastStride_ = strideSize_;
    } else {
      --nbSinceLastStride_;
    }
  }

  explicit stride(size_t strideSize)
      : strideSize_{strideSize-1}, nbSinceLastStride_{0} {}

 private:
  size_t strideSize_;
  size_t nbSinceLastStride_;
};
}  // namespace dfl::pipe

#endif /* PIPES_STEP_HPP */
/**
 * @file take.hpp
 * @author Jonathan Boccara
 * @brief Take pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/take.cpp
 */
#ifndef DFL_TAKE_HPP
#define DFL_TAKE_HPP

namespace dfl::pipe {
class take : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        if (nbTaken_ < nbToTake_) {
            send(FWD(values)..., tailPipeline);
            ++nbTaken_;
        }
    }
    /**
     * @brief Takes N values from e range, drops the rest
     * 
     * @param nbToTake 
     */
    explicit take(std::size_t nbToTake) : nbToTake_{nbToTake}, nbTaken_{0} {}

   private:
    std::size_t nbToTake_;
    std::size_t nbTaken_;
};
}  // namespace dfl::pipe

#endif /* PIPES_TAKE_HPP */
/**
 * @file tap.hpp
 * @author Jonathan Boccara
 * @brief Tap pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/tap.cpp
 */
#ifndef DFL_TAP_HPP
#define DFL_TAP_HPP

namespace dfl::pipe {
template <typename Function>
class tap_pipe : public dfl_base {
   public:
    template <typename Value, typename TailPipeline>
    void onReceive(Value&& value, TailPipeline&& tailPipeline) {
        function_(FWD(value));
        send(FWD(value), tailPipeline);
    }

    template <typename Value>
    void onReceive(Value&& value) {
        function_(FWD(value));
    }

    explicit tap_pipe(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};
/**
 * @brief Forwards the value to a function, as well as the next pipe
 * 
 * @tparam Function 
 * @param function 
 * @return tap_pipe<std::decay_t<Function>> 
 */
template <typename Function>
tap_pipe<std::decay_t<Function>> tap(Function&& function) {
    return tap_pipe<std::decay_t<Function>>(FWD(function));
}
}  // namespace dfl::pipe

#endif /* DFL_TAP_HPP */
/**
 * @file tee.hpp
 * @author Jonathan Boccara
 * @brief Tee pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/tee.cpp
 */
#ifndef DFL_TEE_HPP
#define DFL_TEE_HPP

namespace dfl::pipe {
template <typename TeeBranch>
class tee_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(values..., teeBranch_);
        send(FWD(values)..., tailPipeline);
    }

    explicit tee_pipe(TeeBranch teeBranch) : teeBranch_(teeBranch) {}

   private:
    TeeBranch teeBranch_;
};

template <typename TeeBranch>
tee_pipe<std::decay_t<TeeBranch>> tee(TeeBranch&& predicate) {
    return tee_pipe<std::decay_t<TeeBranch>>{predicate};
}
}  // namespace dfl

#endif /* DFL_TEE_HPP */
/**
 * @file transform.hpp
 * @author Jonathan Boccara
 * @brief Transform pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/transform.cpp
 */
#ifndef DFL_TRANSFORM_HPP
#define DFL_TRANSFORM_HPP

#ifndef DFL_INVOKE_HPP
#define DFL_INVOKE_HPP

#include <functional>
#include <type_traits>

namespace dfl::detail {
template <typename Functor, typename... Args>
typename std::enable_if_t<
    std::is_member_pointer_v<typename std::decay_t<Functor>>,
    typename std::result_of_t<Functor && (Args && ...)>>
invoke(Functor&& f, Args&&... args) {
    return std::mem_fn(f)(std::forward<Args>(args)...);
}

template <typename Functor, typename... Args>
typename std::enable_if_t<
    !std::is_member_pointer_v<typename std::decay_t<Functor>>,
    typename std::result_of_t<Functor && (Args && ...)>>
invoke(Functor&& f, Args&&... args) {
    return std::forward<Functor>(f)(std::forward<Args>(args)...);
}

}  // namespace dfl::detail

#endif /* DFL_INVOKE_HPP */

namespace dfl::pipe {
template <typename Function>
class transform_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(detail::invoke(function_.get(), FWD(values)...), tailPipeline);
    }

    explicit transform_pipe(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};
/**
 * @brief Transforms the value using the function and forwards the returned value
 * 
 * @tparam Function 
 * @param function 
 * @return transform_pipe<Function> 
 */
template <typename Function>
transform_pipe<Function> transform(Function&& function) {
    return transform_pipe<Function>{function};
}
}  // namespace dfl::pipe

#endif /* DFL_TRANSFORM_HPP */
/**
 * @file transform_s.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Transform with state pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/transform_s.cpp
 */
#ifndef DFL_TRANSFORM_S_HPP
#define DFL_TRANSFORM_S_HPP

namespace dfl::pipe {
template <typename Function, typename State>
class transform_s_pipe : public dfl_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        send(FWD(function_(values..., state_)), tailPipeline);
    }

    explicit transform_s_pipe(Function function, State state) : function_(function), state_(state) {}

   private:
    Function function_;
    State state_;
};

/**
 * @brief Applies the function on the value and state, allowing the possibility of changing the state
 * 
 * @tparam Function 
 * @tparam State 
 * @param function 
 * @param state 
 * @return transform_s_pipe<Function, State> 
 */
template <typename Function, typename State>
transform_s_pipe<Function, State> transform_s(Function&& function, State&& state) {
    return transform_s_pipe<Function, State>{function, state};
}
}  // namespace dfl::pipe

#endif /* DFL_TRANSFORM_S_HPP */
/**
 * @file for_each.hpp
 * @author Jonathan Boccara
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/for_each.cpp
 */
#ifndef DFL_CUSTOM_INSERTER_HPP
#define DFL_CUSTOM_INSERTER_HPP

namespace dfl::sink {
template <typename Function>
class for_each_pipeline : public pipeline_base<for_each_pipeline<Function>> {
   public:
    template <typename... T>
    void onReceive(T&&... value) {
        function_(FWD(value)...);
    }

    explicit for_each_pipeline(Function function) : function_(function) {}

   private:
    detail::assignable<Function> function_;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
*/
template <typename InsertFunction>
for_each_pipeline<InsertFunction> for_each(InsertFunction insertFunction) {
    return for_each_pipeline<InsertFunction>(insertFunction);
}
}  // namespace dfl

#endif /* DFL_CUSTOM_INSERTER_HPP */
/**
 * @file hole.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Hole sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/hole.cpp
 */
#ifndef DFL_HOLE_HPP
#define DFL_HOLE_HPP

namespace dfl::sink {
class hole : public pipeline_base<hole> {
   public:
    template <typename T>
    void onReceive(T&&...) {}
    
    /**
     * @brief Discard all values recieved
     */
    hole(){}
};
}  // namespace dfl

#endif /* DFL_HOLE_HPP */
/**
 * @file histogram.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Histogram sink class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example sink/histogram.cpp
 */
#ifndef DFL_HISTOGRAM_HPP
#define DFL_HISTOGRAM_HPP

namespace dfl::sink {
template <typename T>
class histogram_pipeline : public pipeline_base<histogram_pipeline<T>> {
 public:
  template <typename V, typename...Args>
  void onReceive(V&& value, Args... args) {
    _histogram[value] += 1;
    if constexpr (sizeof...(Args) > 0) {
        onReceive(args...);
    }
  }

  histogram_pipeline(T val) : _histogram(val) {}

 private:
  T _histogram;
};

/**
 * Pipe component for creating a histogram of the incoming values
 * @param map
 * @return itself
 */
template <typename T>
histogram_pipeline<T> histogram(T &&val) {
  return histogram_pipeline<T>{val};
}

}  // namespace dfl::sink

#endif /* DFL_HISTOGRAM_HPP */
/**
 * @file for_each.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example sink/min.cpp
 */
#ifndef DFL_SINK_MIN_HPP
#define DFL_SINK_MIN_HPP

namespace dfl::sink {
template <typename T>
class min_pipeline : public pipeline_base<min_pipeline<T>> {
  template <typename Head0, typename Head1, typename... Tail>
  constexpr auto min_val(Head0 &&head0, Head1 &&head1, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) {
      return head0 < head1 ? head0 : head1;
    } else {
      return min_val(min_val(head0, head1), tail...);
    }
  }

 public:
  template <typename... V>
  void onReceive(V &&...value) {
    _min = min_val(_min, value...);
  }

  min_pipeline(T val) : _min(val) {}

 private:
  T _min;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
 */
template <typename T>
min_pipeline<T> min(T &&val) {
  return min_pipeline<T>{val};
}

}  // namespace dfl::sink

#endif /* DFL_SINK_MIN_HPP */
/**
 * @file for_each.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 * @example sink/max.cpp
 */
#ifndef DFL_SINK_MAX_HPP
#define DFL_SINK_MAX_HPP

namespace dfl::sink {
template <typename T>
class max_pipeline : public pipeline_base<max_pipeline<T>> {
 private:
  template <typename Head0, typename Head1, typename... Tail>
  constexpr auto max_val(Head0 &&head0, Head1 &&head1, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) {
      return head0 > head1 ? head0 : head1;
    } else {
      return max_val(max_val(head0, head1), tail...);
    }
  }

 public:
  template <typename... V>
  void onReceive(V &&...value) {
    _max = max_val(_max, value...);
  }

  max_pipeline(T val) : _max(val) {}

 private:
  T _max;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
 */
template <typename T>
max_pipeline<T> max(T &&val) {
  return max_pipeline<T>{val};
}

}  // namespace dfl::sink

#endif /* DFL_SINK_MIN_HPP */
/**
 * @file print.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Print sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/print.cpp
 */
#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>

namespace dfl::sink {

template <char Sep = '\0'>
class print : public pipeline_base<print<Sep>> {
    using OutWriter = Writer<128>;
   public:
    template <typename T>
    constexpr void onReceive(T&& value) {
        if constexpr (Sep == '\0') {
            (*_writer) < value;
        } else {
            (*_writer) < value < Sep;
        }
        _writer->flush();
    }

    /**
     * @brief Prints the incoming value separated by the char template argument
     * 
     * @param fp 
     */
    print(FILE* fp=stdout) {
        _writer = new OutWriter(fp);
    }

   private:
    OutWriter* _writer;
};
}  // namespace dfl::sink

#endif /* PRINT_HPP */
/**
 * @file printf.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Printf sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/printf.cpp
 */
#ifndef DFL_PRINTF_HPP
#define DFL_PRINTF_HPP

#include <functional>

namespace dfl::sink {
template <typename Fmt>
class printf_pipeline : public pipeline_base<printf_pipeline<Fmt>> {
   public:
    template <typename... T>
    void onReceive(T&&... value) {
        printf(_fmt, value...);
    }

    explicit printf_pipeline(Fmt* fmt) : _fmt(fmt) {}

   private:
    const Fmt* _fmt;
};

template <typename Fmt>
printf_pipeline<Fmt> printf(Fmt* fmt) {
    return printf_pipeline<Fmt>(fmt);
}
}  // namespace dfl::sink

#endif /* DFL_PRINTF_HPP */
/**
 * @file push_back.hpp
 * @author Jonathan Boccara
 * @brief Push back sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/push_back.cpp
 */
#ifndef PUSH_BACK_HPP
#define PUSH_BACK_HPP

#include <functional>

namespace dfl::sink {
template <typename Container>
class push_back_pipeline : public pipeline_base<push_back_pipeline<Container>> {
   public:
    template <typename T, typename...Args>
    void onReceive(T&& value, Args... args) {
        container_.get().push_back(FWD(value));
        if constexpr (sizeof...(Args) > 0) {
            onReceive(args...);
        }
    }

    explicit push_back_pipeline(Container& container) : container_(container) {}

   private:
    std::reference_wrapper<Container> container_;
};
/**
 * @brief Pushes the value recieved into the container specified
 * 
 * @tparam Container 
 * @param container 
 * @return push_back_pipeline<Container> 
 */
template <typename Container>
push_back_pipeline<Container> push_back(Container& container) {
    return push_back_pipeline<Container>(container);
}
}  // namespace dfl::sink

#endif /* PUSH_BACK_HPP */
/**
 * @file to_out_stream.hpp
 * @author Jonathan Boccara
 * @brief To out stream sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/to_out_stream.cpp
 */
#ifndef TO_OUT_STREAM_HPP
#define TO_OUT_STREAM_HPP

#include <functional>

namespace dfl::sink {
template <typename OutStream>
class to_out_stream_pipeline : public pipeline_base<to_out_stream_pipeline<OutStream>> {
   public:
    template <typename T>
    void onReceive(T&& value) {
        outStream_.get() << FWD(value);
    }

    explicit to_out_stream_pipeline(OutStream& outStream) : outStream_(outStream) {}

   private:
    std::reference_wrapper<OutStream> outStream_;
};

template <typename OutStream>
to_out_stream_pipeline<OutStream> to_out_stream(OutStream& outStream) {
    return to_out_stream_pipeline<OutStream>(outStream);
}
}  // namespace dfl::sink

#endif /* TO_OUT_STREAM_HPP */
/**
 * @file set_state.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Set state pipeline class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example pipe/set_state.cpp
 */
#ifndef DFL_SINK_SET_VAR_HPP
#define DFL_SINK_SET_VAR_HPP

namespace dfl::sink {
template <typename State>
class set_var_pipe : public pipeline_base<set_var_pipe<State>> {
   public:
    template <typename Value>
    void onReceive(Value&& value) {
        state_ = value;
    }
    /**
     * @brief Sets the state of the given variable
     * 
     * EXAMPLE:
     * int last = 0;
     * gen::range(100)
     * >>= sink::set_var(last);
     * printf("%d\n", max);

    * @tparam State 
    * @param state 
    * @return set_var_pipe<State> 
    */
    explicit set_var_pipe(State state) : state_(state) {}

   private:
    State state_;
};
template <typename State>
set_var_pipe<State> set_var(State&& state) {
    return set_var_pipe<State>{state};
}
}  // namespace dfl::pipe

#endif /* DFL_SINK_SET_STATE_HPP */
/**
 * @file for_each.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief For each sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * @example sink/sum.cpp
 */
#ifndef DFL_SINK_SUM_HPP
#define DFL_SINK_SUM_HPP

namespace dfl::sink {
template <typename T>
class sum_pipeline : public pipeline_base<sum_pipeline<T>> {
   public:
    template<typename... V>
    void onReceive(V&&... value) {
        _acc += (value + ...);
    }

    explicit sum_pipeline(T val) : _acc(val) {}

   private:
    T _acc;
};

/**
 * Pipe component for running a function for each element of a pipeline
 * @param function
 * @return itself
*/
template <typename T>
sum_pipeline<T> sum(T&& val) {
    return sum_pipeline<T>{val};
}
}  // namespace dfl

#endif /* DFL_SINK_SUM_HPP */

/**
 * @file mux.hpp
 * @author Jonathan Boccara
 * @brief Mux generator class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * @example gen/mux.cpp
 */
#ifndef DFL_MUX_HPP
#define DFL_MUX_HPP

#include <tuple>
#include <type_traits>
#include <iostream>

namespace dfl {
namespace gen {

template <typename... Ranges>
struct muxer {
    std::tuple<Ranges const&...> inputs;
    explicit muxer(Ranges const&... inputs) : inputs(inputs...) {}
};

/**
 * @brief Creates conjoined tuples from the ranges supplied
 * 
 * @tparam Ranges 
 * @param ranges 
 * @return auto 
 */
template <typename... Ranges>
auto mux(Ranges&&... ranges) {
    static_assert(sizeof...(Ranges) > 0, "There should be at least one range in mux.");
    return muxer<std::decay_t<Ranges>...>(FWD(ranges)...);
}

}  // namespace gen

namespace detail {
    /*
template <typename... Ts>
bool match_on_any(std::tuple<Ts...> const& tuple1, std::tuple<Ts...> const& tuple2) {
    auto matchOnAny = false;
    detail::for_each2(tuple1, tuple2, [&matchOnAny](auto&& element1, auto&& element2) {
        //if (!matchOnAny && (element1 == element2)) {
            std::cout << "element1: " << element1 << '\n';
            matchOnAny = true;
        //}
    });
    return matchOnAny;
}*/

template <typename... Ts>
bool match_on_any(std::tuple<Ts...> const& tuple1, std::tuple<Ts...> const& tuple2) {
    auto done = false;
    detail::for_each2(tuple1, tuple2, [&done](auto&& begin, auto&& end) {
        done |= (begin == end);
    });
    return done;
}

template <typename... Ts>
void increment(std::tuple<Ts...>& tuple) {
    for_each(tuple, [](auto&& element) { ++element; });
}
}  // namespace detail

/**
 * @brief Connects muxer of ranges to a pipeline
 * 
 * @tparam Ranges 
 * @tparam Pipeline 
 * @param inputsMuxer 
 * @param pipeline 
 */
template <typename... Ranges, typename Pipeline, detail::IsAPipeline<Pipeline> = true>
void operator>>=(gen::muxer<Ranges...> inputsMuxer, Pipeline&& pipeline) {
    auto const beginIterators = detail::transform(inputsMuxer.inputs, [](auto&& range) { return range.begin(); });
    auto const endIterators = detail::transform(inputsMuxer.inputs, [](auto&& range) { return range.end(); });

    for (auto iterators = beginIterators;
         !detail::match_on_any(iterators, endIterators);
         detail::increment(iterators)) {
        sendTupleValues(detail::dereference(iterators), pipeline);
    }
}

}  // namespace dfl

#endif /* PIPES_MUX_HPP */

#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

namespace dfl {
// MK MACRO
// MK(NAME, FUNCTION)
// In function, State = State of class, O = the other incoming variable
#define MK(NAME, FUNC)                                 \
  template <typename State>                            \
  class _##NAME {                                      \
   public:                                             \
    _##NAME(State&& state) : _state(state) {}          \
                                                       \
    template <typename O>                              \
    auto operator()(O o) const {                       \
      return FUNC;                                     \
    }                                                  \
    State _state;                                      \
  };                                                   \
  template <typename State>                            \
  _##NAME<State> NAME(State&& state) {                 \
    return _##NAME<State>{std::forward<State>(state)}; \
  }

auto _not = [](auto x) { return !x; };
auto _not_ = [](auto g) { return [=](auto x) { return !g(x); }; };
auto _even = [](auto x) { return (x & 1) == 0; };
auto _even_ = [](auto g) { return [=](auto x) { return (g(x) & 1) == 0; }; };
auto _odd = [](auto x) { return (x & 1) == 1; };
auto _odd_ = [](auto g) { return [=](auto x) { return (g(x) & 1) == 1; }; };
auto _negate = [](auto x) { return -x; };
auto _negate_ = [](auto g) { return [=](auto x) { return -g(x); }; };
MK(_equal, o == _state);
MK(_equal_, [=](auto x) { return (f(x) == _state); });
MK(_greater_than, o > _state);
MK(_greater_than_, [=](auto x) { return o(x) > _state; });
MK(_greater_than_equal, o >= _state);
MK(_greater_than_equal_, [=](auto x) { return (o(x) >= _state); });
MK(_less_than, o < _state);
MK(_less_than_, [=](auto x) { return (o(x) < _state); });
MK(_less_than_equal, o <= _state);
MK(_less_than_equal_, [=](auto x) { return (o(x) <= _state); });
MK(_addValue, o + _state);
MK(_addValue_, [=](auto x) { return o(x) + _state; });
MK(_mult, o * _state);
MK(_mult_, [=](auto x) { return o(x) * _state; });
MK(_mod, o % _state);
MK(_mod_, [=](auto x) { return o(x) % _state; });

auto _add = [](auto a, auto b) { return a + b; };
auto _add_ = [](auto g) { return [=](auto a, auto b) { return g(a) + b; }; };
auto _max = [](auto a, auto b) { return a > b ? a : b; };
auto _max_ = [](auto g) {
  return [=](auto a, auto b) { return g(a) > b ? g(a) : b; };
};
auto _print = [](auto a) { return std::cout << a << '\n'; };
auto _print_ = [](auto g) {
  return [=](auto a) { std::cout << g(a) << "\n"; };
};
/*
auto _not = [](auto a) { return !a; };
auto _not_ = [](auto g) { return [=](auto x) { return !g(x); }; };
auto _equal = [](auto n) { return [=](auto x) { return x == n; }; };
auto _equal_ = [](auto n) { return [=](auto f) { return [=](auto x) { return
(f(x) == n); }; }; };

auto _even = [](auto a) { return (a&1) == 0; };
auto _even_ = [](auto g) { return [=](auto x) { return (g(x)&1) == 0; }; };
auto _odd = [](auto a) { return (a&1) == 1; };
auto _odd_ = [](auto g) { return [=](auto x) { return (g(x)&1) == 1; }; };

auto _greater_than = [](auto& n) { return [=](auto x) { return x > n; }; };
auto _greater_than_ = [](auto n) { return [=](auto f) { return [=](auto x) {
return (f(x) > n); }; }; }; auto _greater_than_equal = [](auto n) { return
[=](auto f) { return [=](auto x) { return (f(x) > n); }; }; }; auto
_greater_than_equal_ = [](auto n) { return [=](auto f) { return [=](auto x) {
return (f(x) >= n); }; }; }; auto _less_than = [](auto n) { return [=](auto x) {
return x < n; }; }; auto _less_than_ = [](auto n) { return [=](auto f) { return
[=](auto x) { return (f(x) < n); }; }; }; auto _less_than_equal = [](auto n) {
return [=](auto x) { return x <= n; }; }; auto _less_than_equal_ = [](auto n) {
return [=](auto f) { return [=](auto x) { return (f(x) <= n); }; }; };

auto _add = [](auto a, auto b){ return a + b; };
auto _add_ = [](auto g) { return [=](auto a, auto b) { return g(a)+b; }; };
auto _addValue = [](auto n) { return [=](auto x) { return x+n; }; };
auto _addValue_ = [](auto n) { return [=](auto f) { return [=](auto x) { return
(f(x)+n); }; }; }; auto _mod = [](auto n) { return [=](auto x) { return x % n;
}; }; auto _negate = [](auto a) { return -a; }; auto _negate_ = [](auto g) {
return [=](auto x) { return -g(x); }; };

auto _max = [](auto a, auto b){ return a > b ? a : b; };
auto _max_ = [](auto g) { return [=](auto a, auto b) { return g(a) > b ? g(a) :
b; }; };

auto _print = [](auto a) { return std::cout << a << '\n'; };
auto _print_ = [](auto g) { return [=](auto a) { std::cout << g(a) << "\n"; };
};
*/
}  // namespace dfl
#endif

#endif /* DFL_HPP */
