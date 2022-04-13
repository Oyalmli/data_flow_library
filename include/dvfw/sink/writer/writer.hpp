#ifndef WRITER_HPP
#define WRITER_HPP

#include <string>
#include <type_traits>

class Writer {
   private:
    FILE* _fp = stdout;
    char _sep = '\n';

    static const unsigned int BUFFER_SIZE = 1024;
    unsigned char buffer[BUFFER_SIZE];
    int bufferPointer = 0;

    void _flushBuffer() {
        fwrite(buffer, 1, BUFFER_SIZE, _fp);
        bufferPointer = 0;
    }

    constexpr void _write(char c) {
        buffer[bufferPointer++] = c;
        if (bufferPointer >= BUFFER_SIZE) {
            _flushBuffer();
        }
    }

    void _writeStr(std::string str) {
        for (char c : str) {
            _write(c);
        }
    }

   public:
    Writer(char sep = '\n', FILE* outputStream = stdout) {
        _sep = sep;
        _fp = outputStream;
    }

    ~Writer() {
        fclose(_fp);
    }

    void flush() {
        _flushBuffer();
    }

    template <typename T>
    void write(T val) {
        if constexpr (std::is_same_v<T, std::string>) {
            _writeStr(val);
            _write(_sep);
            return;
        }
        if constexpr (std::is_same_v<T, char>) {
            _write(val);
            _write(_sep);
            return;
        }
    }
};

#endif  // WRITER_HPP