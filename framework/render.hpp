#ifndef RENDER_HPP
#define RENDER_HPP

#include "scene.hpp"
#include <string>
#include <glm/glm.hpp>

struct RenderBefehl {
    std::vector<Scene> render_me;

    for(auto i :: render_me){
        render(i);
    }
};




#endif