#include "ray.hpp"

Ray transformRay(glm::mat4 const& mat, Ray const& ray){
      //origin{x,y,z,1}  
      glm::vec3 origin = glm::vec3(mat*glm::vec4(ray.origin_, 1.0f));
      //direction{x,y,z,0}
      glm::vec3 direction = glm::vec3(mat*glm::vec4(ray.direction_,0.0f));  
      return {origin,glm::normalize(direction)};      
}
