#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>

struct Camera{
    std::string name_{" "};
    glm::vec3 pos_{0.0f,0.0f,0.0f};
    glm::vec3 direction_{0.0f,0.0f,-1.0f};
    unsigned int fovX{};
};


#endif