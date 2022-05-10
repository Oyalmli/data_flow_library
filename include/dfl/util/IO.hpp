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
    FILE* _fp = stdout;

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

    template <typename T>
    void write(T val) {
        if constexpr (std::is_same_v<T, char>) {
            _write(val);
            return;
        }
        if constexpr (std::is_same_v<T, const char*>) {
            _writeStr(val, strlen(val));
            return;
        }
        if constexpr (std::is_same_v<T, std::string>) {
            _writeStr(val.c_str(), val.size());
            return;
        }
        if constexpr (std::is_integral_v<T>) {
            std::string s = std::to_string(val);
            _writeStr(s.c_str(), s.size());
            return;
        }
        //DEFAULT 
        std::string s = std::to_string(val);
        _writeStr(s.c_str(), s.size());        
    }

    template <typename T>
    Writer& operator<(T val) {
        write(val);
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
        return (bytesRead > 0);
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
    Reader() : _fp{stdin} {}
    Reader(FILE* inputStream) : _fp{inputStream} {}

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