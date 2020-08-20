#include "camera.hpp"

Camera::Camera():
Camera::Camera(glm::vec3 pos, glm::vec3 direction):
    pos_{pos},
    direction_{direction}{}
Camera::Camera(std::string, glm::vec3 pos, glm::vec3 direction):
    {}