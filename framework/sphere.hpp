#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "hitpoint.hpp"
#include "ray.hpp"


class Sphere : public Shape{
public:
    Sphere(glm::vec3 mid,float rad);
    Sphere(glm::vec3 mid,float rad,std::string name, Color colour);
    ~Sphere() override;
    float area() const override;
    float volume() const override;
    HitPoint intersect(Ray const& ray) const;
    std::ostream& print( std::ostream& os) const override;

private:
    glm::vec3 mid_;
    float radius_;
};

#endif