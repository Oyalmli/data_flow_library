/**
 * @file chunks.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Chunk pipeline class
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_CHUNKS_HPP
#define DVFW_CHUNKS_HPP

namespace dvfw::pipe {
template <typename T, std::size_t N>
class chunks : public dvfw_base {
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
            send(FWD(_curr_chunk), tailPipeline);
            _curr_chunk.clear();
        }
    }

    /**
     * @brief Generates chunks of size N
     */
    explicit chunks() {}

   private:
    std::vector<T> _curr_chunk{};
};
}  // namespace dvfw::pipe

#endif /* PIPES_CHUNKS_HPP */