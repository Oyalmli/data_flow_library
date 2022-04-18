#ifndef IO_HPP
#define IO_HPP

#include <string>
#define MORE ++

template<size_t BUFFER_SIZE>
class Writer {
   private:
    FILE* _fp = stdout;

    unsigned char buffer[BUFFER_SIZE];
    int bufferPointer = 0;

    void _flushBuffer() {
        fwrite(buffer, 1, bufferPointer, _fp);
        bufferPointer = 0;
    }

    constexpr void _write(char c) {
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
        if constexpr (std::is_same_v<T,const char*>) {
            _writeStr(val, std::strlen(val));
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
    
    unsigned char buffer[BUFFER_SIZE];
    int bufferPointer = 0, bytesRead = 0;

    bool _fillBuffer() {
        #ifdef __linux__
            bytesRead = fread_unlocked(buffer, 1, BUFFER_SIZE, _fp);
        #else 
            bytesRead = fread(buffer, 1, BUFFER_SIZE, _fp);
        #endif

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
        for (; c >= '0' && c <= '9'; c = _read()) {
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
    Reader() : _fp{stdin} {}
    Reader(FILE* inputStream) : _fp{inputStream} {}

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

template<size_t R_BUF=128, size_t W_BUF=R_BUF>
class IO {
   public:
    Writer<R_BUF> writer;
    Reader<W_BUF> reader;

    template <typename T>
    IO& operator<<(T val) {
        writer.write(val);
        return *this;
    }

    template <typename T>
    IO& operator>>(T& val) {
        val = reader.template next<T, true>();
        return *this;
    }

    bool operator MORE(){
        return reader.hasNext();
    }
};

#endif