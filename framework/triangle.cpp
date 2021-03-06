#include "triangle.hpp"
#include <glm/gtx/intersect.hpp>

Triangle::Triangle(std::string name,std::shared_ptr<Material> mat, glm::vec3 a, glm::vec3 b, glm::vec3 c):
    Shape(name,mat),
    a_(a),
    b_(b),
    c_(c){}

Triangle::Triangle(std::string name,std::shared_ptr<Material> mat, Color clr, glm::vec3 a, glm::vec3 b, glm::vec3 c):
    Shape(name,clr,mat),
    a_(a),
    b_(b),
    c_(c){}

Triangle::~Triangle(){}

float Triangle::area() const{
    glm::vec3 ab = b_ - a_;
    glm::vec3 ac = c_ - a_;

    return (glm::length(glm::cross(ab,ac))/2);
}
float Triangle::volume() const{
    return 0.0f;
}
HitPoint Triangle::intersect(Ray const& ray) const{
    Ray trans_ray{ray};
    trans_ray.transformRay(world_transform_inv_);
    HitPoint hit;
    glm::vec3 baryPos{0.0f};
    glm::vec3 ab = b_ - a_;
    glm::vec3 ac = c_ - a_;
    glm::vec3 normal = glm::cross(ab,ac); 

    glm::vec3 q = glm::cross(trans_ray.direction_,ac);
    float a = glm::dot(ab,q);
    const float epsilon = 0.0000001;

    if(a > -epsilon && a < epsilon){
        hit.intersection_ = false;
        return hit;
    }
    
    float f = 1/a;
    glm::vec3 s = trans_ray.origin_ - a_;
    float u = f*glm::dot(s,q);

    if(u < 0.0f || u > 1.0f){
        hit.intersection_ = false;
        return hit;
    }

    glm::vec3 w = glm::cross(s,ab);
    float v = f*glm::dot(trans_ray.direction_,w);

    if(v < 0.0f || u+v > 1.0f){
        hit.intersection_ = false;
        return hit;
    }

    float t = f*glm::dot(ac,w);
    if(t > epsilon){
        hit.intersection_ = true;
        hit.intersect_pt_ = trans_ray.origin_ + trans_ray.direction_;
        hit.distance_ = glm::length(hit.intersect_pt_-trans_ray.origin_);
        hit.material_ = material_;
        hit.name_ = name_;
        hit.color_ = color_;
        hit.intersect_direction_= glm::normalize(trans_ray.direction_);
        hit.normal_ = glm::normalize(normal);
        hit.world_transform(world_transform_,world_transform_inv_);
        return hit;        
    }

}
std::ostream& Triangle::print( std::ostream& os) const{
    Shape::print(os);
    std::cout<<"a: "<<a_.x<<", "<<a_.y<<", "<<a_.z<<std::endl;
    std::cout<<"b: "<<b_.x<<", "<<b_.y<<", "<<b_.z<<std::endl;
    std::cout<<"c: "<<c_.x<<", "<<c_.y<<", "<<c_.z<<std::endl;
}