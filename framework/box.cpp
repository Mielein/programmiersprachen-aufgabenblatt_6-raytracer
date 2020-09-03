#include "box.hpp"
#include "tools.hpp"
#include <glm/glm.hpp>
#include <cmath>
#include <vector>
#include <memory>

Box::Box(glm::vec3 min, glm::vec3 max):
    Shape(),
    min_{min},
    max_{max}{}

Box::Box(glm::vec3 min, glm::vec3 max,std::string name, Color colour):
    Shape(name, colour),
    min_{min},
    max_{max}{}

Box::Box(glm::vec3 min, glm::vec3 max,std::string name, Color colour, std::shared_ptr<Material> mat):
    Shape(name, colour, mat),
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

HitPoint Box::intersect(Ray const& ray) const{

    HitPoint hit;
    float distance;

    Plane plane_min_x{min_, glm::vec3{-1,0,0}};
    Plane plane_min_y{min_, glm::vec3{0,-1,0}};
    Plane plane_min_z{min_, glm::vec3{0,0,-1}};
    Plane plane_max_x{max_, glm::vec3{1,0,0}};
    Plane plane_max_y{max_, glm::vec3{0,1,0}};
    Plane plane_max_z{max_, glm::vec3{0,0,1}};

    float dist_min_x = (glm::dot(plane_min_x.normal,plane_min_x.origin)-glm::dot(ray.origin,plane_min_x.normal)/glm::dot(ray.direction,plane_min_x.normal));
    float dist_min_y = (glm::dot(plane_min_y.normal,plane_min_y.origin)-glm::dot(ray.origin,plane_min_y.normal)/glm::dot(ray.direction,plane_min_y.normal));
    float dist_min_z = (glm::dot(plane_min_z.normal,plane_min_z.origin)-glm::dot(ray.origin,plane_min_z.normal)/glm::dot(ray.direction,plane_min_z.normal));
    float dist_max_x = (glm::dot(plane_max_x.normal,plane_max_x.origin)-glm::dot(ray.origin,plane_max_x.normal)/glm::dot(ray.direction,plane_max_x.normal));
    float dist_max_y = (glm::dot(plane_max_y.normal,plane_max_y.origin)-glm::dot(ray.origin,plane_max_y.normal)/glm::dot(ray.direction,plane_max_y.normal));
    float dist_max_z = (glm::dot(plane_max_z.normal,plane_max_z.origin)-glm::dot(ray.origin,plane_max_z.normal)/glm::dot(ray.direction,plane_max_z.normal));

    std::vector<glm::vec3> normals_hit;
    std::vector<glm::vec3> points_hit;
    glm::vec3 hit_point;

    //distance > 0 so it's infront of camera
    if(dist_min_x > 0){
        hit_point = ray.origin + dist_min_x * ray.direction;
        if(hit_point.y <= max_.y && hit_point.y >= min_.y && hit_point.z <= max_.z && hit_point.z >= min_.z){
            points_hit.push_back(hit_point);
            normals_hit.push_back(plane_min_x.normal);
        }
    }    
    if(dist_min_y > 0){
        hit_point = ray.origin + dist_min_y * ray.direction;
        if(hit_point.x <= max_.x && hit_point.x >= min_.x && hit_point.z <= max_.z && hit_point.z >= min_.z){
            points_hit.push_back(hit_point);
            normals_hit.push_back(plane_min_y.normal);
        }
    }
    if(dist_min_z > 0){
        hit_point = ray.origin + dist_min_z * ray.direction;
        if(hit_point.x <= max_.x && hit_point.x >= min_.x && hit_point.y <= max_.y && hit_point.y >= max_.y){
            points_hit.push_back(hit_point);
            normals_hit.push_back(plane_min_z.normal);
        }
    }
        if(dist_max_x > 0){
        hit_point = ray.origin + dist_max_x * ray.direction;
        if(hit_point.y <= max_.y && hit_point.y >= min_.y && hit_point.z <= max_.z && hit_point.z >= min_.z){
            points_hit.push_back(hit_point);
            normals_hit.push_back(plane_max_x.normal);
        }
    }    
    if(dist_max_y > 0){
        hit_point = ray.origin + dist_max_y * ray.direction;
        if(hit_point.x <= max_.x && hit_point.x >= min_.x && hit_point.z <= max_.z && hit_point.z >= min_.z){
            points_hit.push_back(hit_point);
            normals_hit.push_back(plane_max_y.normal);
        }
    }
    if(dist_max_z > 0){
        hit_point = ray.origin + dist_max_z * ray.direction;
        if(hit_point.x <= max_.x && hit_point.x >= min_.x && hit_point.y <= max_.y && hit_point.y >= max_.y){
            points_hit.push_back(hit_point);
            normals_hit.push_back(plane_max_z.normal);
        }
    }
        
    //hit closest to camera
    if(points_hit.size() != 0){
        glm::vec3 closest_hit = points_hit.at(0);
        glm::vec3 closest_normal = normals_hit.at(0);

        for(auto it = 0; it < points_hit.size(); ++it){
            //glm::length(genType const& x) Returns the length of x, i.e., sqrt(x * x)
            distance = glm::length(closest_hit - ray.origin);
            if(glm::length(points_hit.at(it)-ray.origin) < distance){
                distance = glm::length(points_hit.at(it)-ray.origin);
                closest_hit = points_hit.at(it);
                closest_normal = normals_hit.at(it);
            }
        }
        hit.intersection_ = true;
        hit.distance_ = distance;
        hit.colour_ = material_->kd_;
        hit.name_ = name_;
    }

    //printVec(hit_point);
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