#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <set>
#include <string>
#include "material.hpp"
#include "ambient.hpp"
#include "box.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "hitpoint.hpp"
#include "sdfParser.hpp"

struct Scene{
    std::vector<Shape> objects_;
    std::map<std::string, Camera> cameras_;
    std::map<std::string, Light> lightsources_;
    Ambient background_;
    
};


#endif