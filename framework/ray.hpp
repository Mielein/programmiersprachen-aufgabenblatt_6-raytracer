#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <string>

struct Ray{
glm::vec3 origin_ = {0.0f,0.0f,0.0f};
glm::vec3 direction_ = {0.0f,0.0f,-1.0f};

Ray transformRay(glm::mat4 const& mat) const{
      //origin{x,y,z,1}  
      glm::vec3 origin = glm::vec3(mat*glm::vec4(origin_, 1.0f));
      //direction{x,y,z,0}
      glm::vec3 direction = glm::vec3(mat*glm::vec4(direction_,0.0f));  
      //std::cout<< "origin: "<<origin.x<<","<<origin.y<<","<<origin.z<<"\n"<<"diection: "<<glm::normalize(direction).x<<","<<glm::normalize(direction).y<<","<<glm::normalize(direction).z<<std::endl;

      return {origin,glm::normalize(direction)};

/*       glm::vec3 origin{mat*glm::vec4(origin_, 1.0f)};
      glm::vec3 direction{mat*glm::vec4(direction_, 0.0f)};

      direction = glm::normalize(direction);

      return{{origin.x,origin.y,origin.z},{direction.x,direction.y,direction.z}}; */
      
}
};

#endif