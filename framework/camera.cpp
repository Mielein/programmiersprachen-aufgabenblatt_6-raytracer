#include "camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 direction):
    name_{"default cam name"},
    pos_{pos},
    direction_{direction}{}

Camera::Camera(std::string name, glm::vec3 pos, glm::vec3 direction):
    name_{name},
    pos_{pos},
    direction_{direction}{}