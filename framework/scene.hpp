#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <ostream>
#include <memory>
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
    std::vector<std::shared_ptr<Shape>> shape_vec; 
    std::vector<std::shared_ptr<Light>> light_vec;
    std::vector<std::shared_ptr<Material>> mat_vec;
    Camera camera_;
    Ambient background_;
};

Scene sdfParser(std::string const& file);

#endif