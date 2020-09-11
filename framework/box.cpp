#include "box.hpp"
#include <glm/glm.hpp>
#include <cmath>
#include <vector>
#include <memory>

Box::Box():
    Shape(),
    min_{0.0f},
    max_{0.0f}{}

Box::Box(glm::vec3 min, glm::vec3 max):
    Shape(),
    min_{0.0f},
    max_{0.0f}{}

Box::Box(glm::vec3 min, glm::vec3 max,std::string name, Color color):
    Shape(name, color)
    {
        min_ = checkMin(min, max);
        max_ = checkMax(min, max);
    }

Box::Box(glm::vec3 min, glm::vec3 max,std::string name, Color color, std::shared_ptr<Material> mat):
    Shape(name, color, mat)
    {
        min_ = checkMin(min, max);
        max_ = checkMax(min, max);
    }
   

float Box::area() const{
    float x = min_.x - max_.x;
    float y = min_.y - max_.y;
    float z = min_.z - max_.z;
    return abs(2*x*y)+abs(2*x*z)+abs(2*y*z);
}

float Box::volume() const{
    return abs((min_.x-max_.x)*(min_.y-max_.y)*(min_.z-max_.z));
}

glm::vec3 checkMax(glm::vec3 input1, glm::vec3 input2){
    glm::vec3 tmp;

    if (input1.x >= input2.x){
        tmp.x = input1.x;}
    else{tmp.x = input2.x;}
    
    if (input1.y >= input2.y){
        tmp.y = input1.y;}
    else{tmp.y = input2.y;}

    if (input1.z >= input2.z){
        tmp.z = input1.z;}
    else{tmp.z = input2.z;}

    return tmp;
};

glm::vec3 checkMin(glm::vec3 input1, glm::vec3 input2){
    glm::vec3 tmp;

    if (input1.x <= input2.x){
        tmp.x = input1.x;}
    else{tmp.x = input2.x;}
    
    if (input1.y <= input2.y){
        tmp.y = input1.y;}
    else{tmp.y = input2.y;}

    if (input1.z <= input2.z){
        tmp.z = input1.z;}
    else{tmp.z = input2.z;}

    return tmp;
};

HitPoint Box::intersect(Ray const& ray) const{
    HitPoint hit;
    bool was_hit = false;
    float tmin = FLT_MAX;
    Ray ray_local{ray};
    ray_local.transformRay(world_transform_inv_); 

    float tmin_x = (min_.x-ray_local.origin_.x)/ray_local.direction_.x;
    float tmax_x = (max_.x-ray_local.origin_.x)/ray_local.direction_.x;
    glm::vec3 p_x_min = ray_local.origin_ + tmin_x*ray_local.direction_;
    glm::vec3 p_x_max = ray_local.origin_ + tmax_x*ray_local.direction_;

    float tmin_y = (min_.y-ray_local.origin_.y)/ray_local.direction_.y;
    float tmax_y = (max_.y-ray_local.origin_.y)/ray_local.direction_.y;

    glm::vec3 p_y_min = ray_local.origin_ + tmin_y*ray_local.direction_;
    glm::vec3 p_y_max = ray_local.origin_ + tmax_y*ray_local.direction_;   

    float tmin_z = (min_.z-ray_local.origin_.z)/ray_local.direction_.z;
    float tmax_z = (max_.z-ray_local.origin_.z)/ray_local.direction_.z;

    glm::vec3 p_z_min = ray_local.origin_ + tmin_z*ray_local.direction_;
    glm::vec3 p_z_max = ray_local.origin_ + tmax_z*ray_local.direction_;

    if(p_x_min.y <= max_.y && p_x_min.y >= min_.y && p_x_min.z <= max_.z && p_x_min.z >= min_.z){
        was_hit = true;
        hit.intersect_pt_ = p_x_min;
        tmin = tmin_x;
        hit.normal_ = glm::vec3{-1.0f,0.0f,0.0f};
    }
    if(p_x_max.y <= max_.y && p_x_max.y >= min_.y && p_x_max.z <= max_.z && p_x_max.z >= min_.z){
        was_hit = true;
        if(tmin_x > tmax_x){
            hit.intersect_pt_ = p_x_max;
            tmin = tmax_x;
            hit.normal_ = glm::vec3{1.0f,0.0f,0.0f};
        }
    }

    if(p_y_min.x <= max_.x && p_y_min.x >= min_.x && p_y_min.z <= max_.z && p_y_min.z >= min_.z){
        was_hit = true;
        if(tmin > tmin_y){
            hit.intersect_pt_ = p_y_min;
            tmin = tmin_y;
            hit.normal_ = glm::vec3{0.0f,-1.0f,0.0f};  
        }
    }

    if(p_y_max.x <= max_.x && p_y_max.x >= min_.x && p_y_max.z <= max_.z && p_y_max.z >= min_.z){
        was_hit = true;
        if(tmin > tmax_y){
            hit.intersect_pt_ = p_y_max;
            tmin = tmax_y;
            hit.normal_ = glm::vec3{0.0f,1.0f,0.0f};
        }
    }

    if(p_z_min.x <= max_.x && p_z_min.x >= min_.x && p_z_min.y <= max_.y && p_z_min.y >= min_.y){
        was_hit = true;
        if(tmin > tmin_z){
            hit.intersect_pt_ = p_z_min;
            tmin = tmin_z;
            hit.normal_ = glm::vec3{0.0f,0.0f,-1.0f};    
        }
    }
    if(p_z_max.x <= max_.x && p_z_max.x >= min_.x && p_z_max.y <= max_.y && p_z_max.y >= min_.y){
        was_hit = true;
        if(tmin > tmax_z){
            hit.intersect_pt_ = p_z_max;
            tmin = tmax_z;
            hit.normal_ = glm::vec3{0.0f,0.0f,1.0f};   
        } 
    }
    if(was_hit == true){
        hit.intersection_ = true;
        hit.intersect_direction_ = ray.direction_;
        hit.distance_ = tmin;
        hit.world_transform(world_transform_,world_transform_inv_);
    } 
    return hit; 
    
 } 

std::ostream& Box::print( std::ostream& os) const{
    Shape::print(os);
    os<<"minimum: "<<min_.x<<", "<<min_.y<<", "<<min_.z<<"\n";
    os<<"maximum: "<<max_.x<<", "<<max_.y<<", "<<max_.z<<"\n";
    os<<"volume: "<<(*this).area()<<"\n";
    os<<"surface area: "<<(*this).volume()<<"\n";
    return os;
}