#include "shape.hpp"

Shape::Shape():
    name_{" "},
    color_{1.0f,0.0f,0.0f}{}

Shape::Shape(std::string name, Color color):
    name_{name},
    color_{color}{}

Shape::Shape(std::string name, Color color,std::shared_ptr<Material> material):
    name_{name},
    color_{color},
    material_{material}{}

Shape::~Shape(){
    std::cout<<"Shape destructor is here to destruct!!"<<std::endl;
}

std::shared_ptr<Material> Shape::getMat() const{
    return material_;
}

std::ostream& Shape::print( std::ostream& os) const{
    os<<"name: "<<name_<<"\n"<<"color: "<<color_;
    return os;
}
std::ostream& operator<<(std::ostream& os ,Shape const& s){
    return s.print(os);
}