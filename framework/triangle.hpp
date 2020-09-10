#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape {
    public:
    Triangle(std::string name,std::shared_ptr<Material> mat, glm::vec3 a, glm::vec3 b, glm::vec3 c);
    Triangle(std::string name,std::shared_ptr<Material> mat,Color clr,glm::vec3 a, glm::vec3 b, glm::vec3 c);
    ~Triangle() override;
    float area() const override;
    float volume() const override;
    HitPoint intersect(Ray const& ray) const;
    std::ostream& print( std::ostream& os) const;

    private:
    glm::vec3 a_;
    glm::vec3 b_;
    glm::vec3 c_;
};


#endif