#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"

struct Light {
    
    std::string name_{" "};
    glm::vec3 pos_{0.0f,0.0f,0.0f};
    Color colour_{0.0f,0.0f,0.0f};
    float brightness = 0.0f;

};


#endif