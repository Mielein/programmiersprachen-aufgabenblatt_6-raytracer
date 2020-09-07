#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>

struct Camera{
    std::string name_{" "};
    glm::vec3 pos_{0.0f,0.0f,0.0f};
    glm::vec3 direction_{0.0f,0.0f,-1.0f};
    /* unsigned  */float fovX{45.0f};



/*     Ray constructEyeRay(float x, float y, float width, float height) const {
        glm::vec3 origin{0,0,0};
        glm::vec3 direction = glm::normalize(glm::vec3{x-(width*0.5f),y-(height*0.5f),-(width/2.0f)/tan((fovX/2.0f)*M_PI/180)});
           // cout<<rayDirection.x<<" "<<rayDirection.y<<" "<<rayDirection.z<<endl;
		return Ray{origin,direction};
    }  */
};


#endif