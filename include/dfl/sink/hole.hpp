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