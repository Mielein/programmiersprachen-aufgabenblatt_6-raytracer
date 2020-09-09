#include "triangle.hpp"
#include <glm/gtx/intersect.hpp>


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
    float distance = 1.0f;
    glm::vec3 baryPos{0.0f};
    glm::vec3 ab = b_ - a_;
    glm::vec3 ac = c_ - a_;
    glm::vec3 c = glm::cross(ab,ac);
    glm::vec3 normal = c; 
    bool did_it_hit = glm::intersectRayTriangle(ray.origin_,glm::normalize(ray.direction_),a_,b_,c_,baryPos,distance);
    return{did_it_hit,distance,name_,color_,ray.origin_+(distance*ray.direction_),glm::normalize(ray.direction_),normal};
}
std::ostream& Triangle::print( std::ostream& os) const{

}