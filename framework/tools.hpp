#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <glm/vec3.hpp>

void printVec(glm::vec3 const& vec){
    std::cout<< "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << std::endl;
}

void printColor(Color const& color){
    std::cout<< "r: " << color.r << ", g: " << color.g << ", b: "<< color.b << std::endl;
}

#endif