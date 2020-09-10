#ifndef RENDER_HPP
#define RENDER_HPP

#include "scene.hpp"
#include <string>
#include <glm/glm.hpp>

struct Render {
    unsigned w;
    unsigned h; 
    std::string const& file; 
    unsigned depth;
};




#endif