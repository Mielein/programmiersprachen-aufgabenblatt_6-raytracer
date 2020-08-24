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

#include <iostream> //debug prints
#include <fstream> //open / read / write / close files
#include <sstream> //stringstram -> easy parsing mechanics
#include <string> //buffer lines read from file
#include <glm/vec3.hpp>

struct Scene{
    std::vector<Shape> objects_;
    std::map<std::string, Camera> cameras_;
    std::map<std::string, Light> lightsources_;
    Ambient background_;
};

Scene sdfParser(std::string const& file);

#endif