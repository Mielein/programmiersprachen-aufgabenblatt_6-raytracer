#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>


class Box : public Shape{
    public:
    Box();
    Box(glm::vec3 min, glm::vec3 max);
    Box(glm::vec3 min, glm::vec3 max,std::string name, Color color);
    Box(glm::vec3 min, glm::vec3 max,std::string name, Color color, std::shared_ptr<Material> mat);
    float area() const override;
    float volume() const override;

    HitPoint intersect(Ray const& ray) const override;
    std::ostream& print( std::ostream& os) const override;
    
    private:
    glm::vec3 min_;
    glm::vec3 max_;
};
    glm::vec3 checkMax(glm::vec3 input1, glm::vec3 input2);
    glm::vec3 checkMin(glm::vec3 input1, glm::vec3 input2);

#endif