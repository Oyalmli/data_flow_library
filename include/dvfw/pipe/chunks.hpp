#ifndef DVFW_CHUNKS_HPP
#define DVFW_CHUNKS_HPP

namespace dvfw {
namespace pipe {
template <typename T>
class chunks : public dvfw_base {
   public:
    template <typename... Values, typename TailPipeline>
    void onReceive(Values&&... values, TailPipeline&& tailPipeline) {
        _curr_chunk.push_back(values...);
        if (_curr_chunk.size() >= _chunk_size) {
            send(FWD(_curr_chunk), tailPipeline);
            _curr_chunk.clear();
        }
    }

    explicit chunks(std::size_t chunk_size) : _chunk_size{chunk_size} {
        _curr_chunk = {};
    }

   private:
    std::size_t _chunk_size;
    std::vector<T> _curr_chunk;
};
}  // namespace pipe
}  // namespace dvfw

#endif /* PIPES_CHUNKS_HPP */