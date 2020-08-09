#include "sphere.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

Sphere::Sphere(glm::vec3 mid,float rad):
    Shape(),
    mid_{mid},
    radius_{abs(rad)}{
        if(radius_< 0){
            std::cout<<"your radius has been turned positive";
        }
        if(radius_ == 0){
            std::cout<<"your sphere will not be visible with a radius of 0"<<std::endl;
        } 
    }

Sphere::Sphere(glm::vec3 mid,float rad,std::string name,Color colour):
    Shape(name,colour),
    mid_{mid},
    radius_{rad}{}

Sphere::~Sphere(){
    std::cout<<"a wild sphere destructor has appeared"<<std::endl;
}
    
float Sphere::area() const{
    return 4*M_PI*pow(radius_,2);
}
float Sphere::volume() const{
    return M_PI*pow(radius_,3)*4/3;
}
HitPoint Sphere::intersect(Ray const& ray) const{
    float distance = 1.0f;
    bool did_it_hit = glm::intersectRaySphere(ray.origin,glm::normalize(ray.direction), mid_, pow(radius_,2),distance);
    return HitPoint{did_it_hit,distance,name_,colour_,ray.origin+(distance*ray.direction),glm::normalize(ray.direction)};
}
std::ostream& Sphere::print(std::ostream& os) const{
    Shape::print(os);
    os<<"center: "<<mid_.x<<", "<<mid_.y<<", "<<mid_.z<<"\n";
    os<<"radius: "<<radius_<<"\n";
    os<<"volume: "<<(*this).area()<<"\n";
    os<<"surface area: "<<(*this).volume()<<"\n";
    return os;
}