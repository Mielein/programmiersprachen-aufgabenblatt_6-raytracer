#include "hitpoint.hpp"

void world_transform(glm::mat4 const& mat, glm::mat4 const& inv_mat,HitPoint hit){
    hit.intersect_pt_ = glm::vec3(mat*glm::vec4(hit.intersect_pt_, 1.0f));
    hit.normal_= glm::normalize(glm::vec3(glm::transpose(inv_mat)*glm::vec4(hit.normal_, 0.0f)));
} 