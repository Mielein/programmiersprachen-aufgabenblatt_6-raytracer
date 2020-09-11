#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

//now single threaded again
int main(int argc, char* argv[])
{
/*     std::cout << "Hallu ich bin eine animation" << std::endl;
 */ unsigned const image_width = 500;
    unsigned const image_height = 500;
    for(int i = 0; i < 360; i++){
    std::cout << i << std::endl;
    float cam_value = i * 0.2f;
    std::string name =  "./animation_files/pic" + std::to_string(i) + ".ppm" ;
    std::string const filename = name;
    Renderer renderer{image_width, image_height, filename};
    
    Scene scene = sdfParser("../../source/raytracer.sdf");
    scene.camera_.direction_.z = scene.camera_.direction_.z + cam_value;
    renderer.render(scene);

    }
    
    
    
    

}