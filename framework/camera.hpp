#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>

class Camera{
public:
    Camera(glm::vec3 pos, glm::vec3 direction);
    Camera(std::string name,glm::vec3 pos, glm::vec3 direction);
private:
    std::string name_{" "};
    glm::vec3 pos_{0.0f,0.0f,0.0f};
    glm::vec3 direction_{0.0f,0.0f,0.0f};
};


#endif