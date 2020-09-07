#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <string>

struct Ray{
glm::vec3 origin_ = {0.0f,0.0f,0.0f};
glm::vec3 direction_ = {0.0f,0.0f,-1.0f};

Ray transform(glm::mat4 const& mat) const{
      //origin{x,y,z,1}  
      glm::vec3 origin = glm::vec3(mat*glm::vec4(origin_, 1.0f));
      //direction{x,y,z,0}
      glm::vec3 direction = glm::vec3(mat*glm::vec4(direction_,0.0f));  
      return {origin,glm::normalize(direction)};
}
};

#endif