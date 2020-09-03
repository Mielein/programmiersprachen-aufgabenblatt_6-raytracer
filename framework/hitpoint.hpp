#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <string>
#include "color.hpp"
#include <memory>

struct HitPoint{

    bool intersection_ = false;
    float distance_ = INFINITY;
    std::string name_ = " ";
    Color color_{1.0f,0.0f,0.0f};
    glm::vec3 intersect_pt_{0.0f,0.0f,0.0f};
    glm::vec3 intersect_direction_{1.0f,1.0f,1.0f};
    glm::vec3 normal_;
    std::shared_ptr<Material> material_;

    //intersect_pt and normal to world space
/*     void world_transform(glm::mat4 const& mat, glm::mat4 const& inv_mat){
        intersect_pt_ = glm::vec3(mat*glm::vec4(intersect_pt_, 1.0f));
        normal_= glm::normalize(glm::vec3(inv_mat*glm::vec4(normal_, 0.0f)));
    } */
};


#endif