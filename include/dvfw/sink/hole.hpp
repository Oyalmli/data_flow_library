/**
 * @file hole.hpp
 * @author Øyvind Almli (oyvind.almli@gmail.com)
 * @brief Hole sink class
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DVFW_HOLE_HPP
#define DVFW_HOLE_HPP

namespace dvfw::sink {
class hole : public pipeline_base<hole> {
   public:
    template <typename T>
    void onReceive(T&&) {}
    
    /**
     * @brief Discard all values recieved
     */
    hole(){}
};
};  // namespace dvfw

#endif /* DVFW_HOLE_HPP */