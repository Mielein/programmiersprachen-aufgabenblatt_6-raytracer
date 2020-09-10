#include "hitpoint.hpp"

void world_transform(glm::mat4 const& mat, glm::mat4 const& inv_mat){
    intersect_pt_ = glm::vec3(mat*glm::vec4(intersect_pt_, 1.0f));
    normal_= glm::normalize(glm::vec3(glm::transpose(inv_mat)*glm::vec4(normal_, 0.0f)));
} 