#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"

struct Light {
    
    Light(){};

    Light(std::string name, glm::vec3 pos, Color color, float brightness):
        name_{name},
        pos_{pos},
        color_{color},
        brightness_{brightness}{}
        
    std::string name_{" "};
    glm::vec3 pos_{0.0f,0.0f,0.0f};
    Color color_{0.0f,0.0f,0.0f};
    float brightness_ = 0.0f;

};


#endif