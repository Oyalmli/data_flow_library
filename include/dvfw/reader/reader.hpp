#pragma once
#include <string>
#include <type_traits>

class Reader {
   private:
    FILE* _fp = stdin;
    
    static const unsigned int BUFFER_SIZE = 256;
    unsigned char buffer[BUFFER_SIZE];
    int bufferPointer = 0, bytesRead = 0;

    bool _fillBuffer() {
        bytesRead = fread(buffer, 1, BUFFER_SIZE, _fp);
        bufferPointer = 0;
        return (bytesRead > 0);
    }

    constexpr char _read() {
        if (!hasNext()) return '\0';
        return buffer[bufferPointer++];
    }

    template <typename T>
    constexpr T _readUnsignedInteger() {
        T ret = 0;
        char c = _read();
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
        char c = _read();
        for (; (c < '0' || c > '9') && c != '\0'; c = _read()) {
            neg = (c == '-');
        }
        for (; (c >= '0' && c <= '9'); c = _read()) {
            ret = ret * 10 + (c - '0');
        }
        return neg ? -ret : ret;
    }

    template <typename T>
    constexpr T _readFloating() {
        T pow10 = 1, left = 0, right = 0;
        bool neg = false;
        unsigned c = _read();
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
        char c = _read();
        for (; std::isspace(c) && c != '\0'; c = _read())
            ;
        for (; !std::isspace(c) && c != '\0'; c = _read()) {
            res.push_back(c);
        }
        return res;
    }

    std::string _readLine() {
        std::string res;
        for (char c = _read(); c != '\n' && c != '\0'; c = _read()) {
            res.push_back(c);
        }
        return res;
    }

   public:
    Reader() = default;
    Reader(FILE* inputStream) {
        _fp = inputStream;
    }

    ~Reader() {
        fclose(_fp);
    }

    std::string getWord() { return _readWord(); }
    std::string getLine() { return _readLine(); }

    constexpr char getChar() {
        return _read();
    }

    constexpr bool hasNext() {
        return (bufferPointer < bytesRead) || _fillBuffer();
    }

    void skipToken() {
        unsigned c = _read();
        for (; std::isspace(c) && c != '\0'; c = _read());
        for (; !std::isspace(c); c = _read());
    }

    template <typename T>
    constexpr T next() {
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
};
