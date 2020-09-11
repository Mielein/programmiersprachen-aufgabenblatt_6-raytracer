#include "shape.hpp"

Shape::Shape():
    name_{" "},
    color_{1.0f,0.0f,0.0f},
    world_transform_{glm::vec4{1.0f,0.0f,0.0f,0.0f},glm::vec4{0.0f,1.0f,0.0f,0.0f},glm::vec4{0.0f,0.0f,1.0f,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}},
    world_transform_inv_(glm::inverse(world_transform_)){}

Shape::Shape(std::string name, Color color):
    name_{name},
    color_{color},
    world_transform_{glm::vec4{1.0f,0.0f,0.0f,0.0f},glm::vec4{0.0f,1.0f,0.0f,0.0f},glm::vec4{0.0f,0.0f,1.0f,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}},
    world_transform_inv_(glm::inverse(world_transform_)){}

Shape::Shape(std::string name, std::shared_ptr<Material> material):
    name_{name},
    color_{1.0f,1.0f,1.0f},
    material_{material},
    world_transform_{glm::vec4{1.0f,0.0f,0.0f,0.0f},glm::vec4{0.0f,1.0f,0.0f,0.0f},glm::vec4{0.0f,0.0f,1.0f,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}},
    world_transform_inv_(glm::inverse(world_transform_)){}    

Shape::Shape(std::string name, Color color,std::shared_ptr<Material> material):
    name_{name},
    color_{color},
    material_{material},
    world_transform_{glm::vec4{1.0f,0.0f,0.0f,0.0f},glm::vec4{0.0f,1.0f,0.0f,0.0f},glm::vec4{0.0f,0.0f,1.0f,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}},
    world_transform_inv_(glm::inverse(world_transform_)){}

Shape::~Shape(){
    //std::cout<<"Shape destructor is here to destruct!!"<<std::endl;
}

std::shared_ptr<Material> Shape::getMat() const{
    return material_;
}

std::string Shape::getName() const{
    return name_;
}

glm::mat4 Shape::getWorldInv() const{
    return world_transform_inv_;
}
void Shape::transformation(glm::mat4 const& mat){
    world_transform_ *= mat;
    world_transform_inv_ = glm::inverse(world_transform_);
}
void Shape::rotate(float angle,  glm::vec3 const& axis){
    world_transform_ = glm::rotate(world_transform_,angle,axis); 
    world_transform_inv_ = glm::inverse(world_transform_);

}
void Shape::scale(glm::vec3 const& scale_vec){
    world_transform_ = glm::scale(world_transform_,scale_vec);
    world_transform_inv_ = glm::inverse(world_transform_);
}
    
void Shape::translate(glm::vec3 transl_vec){
    world_transform_ = glm::translate(world_transform_,transl_vec); 
    world_transform_inv_ = glm::inverse(world_transform_);
}
std::ostream& Shape::print( std::ostream& os) const{
    os<<"name: "<<name_<<"\n"<<"color: "<<color_;
    return os;
}
std::ostream& operator<<(std::ostream& os ,Shape const& s){
    return s.print(os);
}