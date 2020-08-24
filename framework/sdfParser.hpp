#include <iostream> //debug prints
#include <fstream> //open / read / write / close files
#include <sstream> //stringstram -> easy parsing mechanics
#include <string> //buffer lines read from file
#include <glm/vec3.hpp>
#include "scene.hpp"



Scene sdfParser(std::string const& file);
