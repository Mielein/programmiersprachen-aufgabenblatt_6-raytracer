#include "sphere.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <memory>

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

Sphere::Sphere(glm::vec3 mid,float rad,std::string name, Color color):
    Shape(name,color),
    mid_{mid},
    radius_{rad}{}

Sphere::Sphere(std::string name,Color color,std::shared_ptr<Material> mat,glm::vec3 mid,float rad):
    Shape(name,color,mat),
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
    Ray trans_ray;
    trans_ray.transformRay(world_transform_inv_,ray);
    float distance = 1.0f;
    bool did_it_hit = glm::intersectRaySphere(ray.origin_,glm::normalize(ray.direction_), mid_, pow(radius_,2),distance);
    HitPoint hit_sphere{did_it_hit,distance,name_,color_,ray.origin_+(distance*ray.direction_),glm::normalize(ray.direction_)};
    hit_sphere.normal_ = glm::normalize(mid_-hit_sphere.intersect_pt_);
    hit_sphere.world_transform(world_transform_,world_transform_inv_);
    return hit_sphere;
}
std::ostream& Sphere::print(std::ostream& os) const{
    Shape::print(os);
    os<<"center: "<<mid_.x<<", "<<mid_.y<<", "<<mid_.z<<"\n";
    os<<"radius: "<<radius_<<"\n";
    os<<"volume: "<<(*this).area()<<"\n";
    os<<"surface area: "<<(*this).volume()<<"\n";
    return os;
}