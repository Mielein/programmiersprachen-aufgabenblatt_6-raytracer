#include "box.hpp"
#include <cmath>

Box::Box(glm::vec3 min, glm::vec3 max):
    Shape(),
    min_{min},
    max_{max}{}

Box::Box(glm::vec3 min, glm::vec3 max,std::string name, Color colour):
    Shape(name, colour),
    min_{min},
    max_{max}{}
    

float Box::area() const{
    float x = min_.x - max_.x;
    float y = min_.y - max_.y;
    float z = min_.z - max_.z;
    return abs(2*x*y)+abs(2*x*z)+abs(2*y*z);
}

float Box::volume() const{
    return abs((min_.x-max_.x)*(min_.y-max_.y)*(min_.z-max_.z));
}

std::ostream& Box::print( std::ostream& os) const{
    Shape::print(os);
    os<<"minimum: "<<min_.x<<", "<<min_.y<<", "<<min_.z<<"\n";
    os<<"maximum: "<<max_.x<<", "<<max_.y<<", "<<max_.z<<"\n";
    os<<"volume: "<<(*this).area()<<"\n";
    os<<"surface area: "<<(*this).volume()<<"\n";
    return os;
}