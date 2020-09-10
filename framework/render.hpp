#ifndef RENDER_HPP
#define RENDER_HPP

#include "scene.hpp"
#include <string>
#include <glm/glm.hpp>

<<<<<<< HEAD
struct RenderBefehl {
    //std::vector<Scene> render_me;

    /* for(auto i :: render_me){
        render(i);
    } */
=======
struct Render {
    unsigned w;
    unsigned h; 
    std::string const& file; 
    unsigned depth;
>>>>>>> 0a92cd5c3e36056da40977bb6cb9dda85d2d2887
};




#endif