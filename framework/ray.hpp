#ifndef RAY_HPP
#define RAY_HPP

#include "hitpoint.hpp"
#include "shape.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <string>

struct Ray{
glm::vec3 origin_ = {0.0f,0.0f,0.0f};
glm::vec3 direction_ = {0.0f,0.0f,-1.0f};

Ray transformRay(glm::mat4 const& mat, Ray const& ray);
};

#endif