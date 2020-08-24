#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <set>
#include "material.hpp"
#include "ambient.hpp"
#include "box.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "hitpoint.hpp"
#include "sdfParser.hpp"

struct Scene{
    Camera Beobachter();
    
};


#endif