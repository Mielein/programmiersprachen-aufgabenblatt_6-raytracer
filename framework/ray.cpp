#include "ray.hpp"

void Ray::transformRay(glm::mat4 const& mat){
      //origin{x,y,z,1}  
      origin_ = glm::vec3(mat*glm::vec4(origin_, 1.0f));
      //direction{x,y,z,0}
      direction_ = glm::vec3(mat*glm::vec4(direction_,0.0f));  
}