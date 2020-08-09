#include "shape.hpp"

Shape::Shape():
name_{" "},
colour_{1.0f,0.0f,0.0f}{}

Shape::Shape(std::string name, Color colour):
name_{name},
colour_{colour}{}

Shape::~Shape(){
    std::cout<<"Shape destructor is here to destruct!!"<<std::endl;
}

std::ostream& Shape::print( std::ostream& os) const{
    os<<"name: "<<name_<<"\n"<<"colour: "<<colour_;
    return os;
}
std::ostream& operator<<(std::ostream& os ,Shape const& s){
    return s.print(os);
}