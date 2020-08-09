#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"

struct HitPoint{

    bool intersection = false;
    float distance = 0.0f;
    std::string name = " ";
    Color colour{1.0f,0.0f,0.0f};
    glm::vec3 intersect_pt{0.0f,0.0f,0.0f};
    glm::vec3 intersect_direction{1.0f,1.0f,1.0f};


};


#endif