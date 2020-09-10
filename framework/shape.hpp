#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include "material.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <iostream>
#include <memory>
#include <glm/glm.hpp>

class Shape{
    public:
    Shape();
    Shape(std::string name, Color color);
    Shape(std::string name, std::shared_ptr<Material> material);
    Shape(std::string name, Color color,std::shared_ptr<Material> material);
    virtual ~Shape();
    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual HitPoint intersect(Ray const& ray) const = 0;
    virtual std::ostream& print( std::ostream& os) const;
    std::string getName() const;
    std::shared_ptr<Material> getMat() const;
    void transformation(glm::mat4 const& mat);
    glm::mat4 getWorldInv() const;

    protected:
    std::string name_;
    Color color_{1.0f,0.0f,0.0f};
    std::shared_ptr<Material> material_;
    glm::mat4 world_transform_;
    glm::mat4 world_transform_inv_;
};

std::ostream& operator<<(std::ostream& os ,Shape const& s);

#endif