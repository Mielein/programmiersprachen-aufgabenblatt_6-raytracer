#include "../framework/fensterchen.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include <GLFW/glfw3.h>
#include <utility>
#include <cmath>


int main(int argc, char* argv[]){

  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./example.ppm";

  Renderer renderer{image_width, image_height, filename};

  std::cout<<"reading sdf"<<std::endl;
  std::vector<std::shared_ptr<Shape>> shape_vec; 
  std::vector<std::shared_ptr<Light>> light_vec;
  std::map<std::string,std::shared_ptr<Material>> mat_map;
  Sphere sphere{{500.0,500.0,-1000.0}, 500.0f ,"pussy",{0.0,0.0,1.0}};
  std::shared_ptr<Shape>spheres = std::make_shared<Sphere>(sphere);
  shape_vec.push_back(spheres);
  Light light{};
  std::shared_ptr<Light>lights = std::make_shared<Light>(light);
  light_vec.push_back(lights);
  Camera cam{};
  Ambient amby{"a",{1.0,0.2,1.4}};
  Scene s{shape_vec,light_vec,mat_map,cam,amby};
  /* sdfParser("/home/marie/programmiersprachen-aufgabenblatt_6-raytracer/source/example.sdf"); */

/*   for (auto a : s.shape_vec){
    std::cout<< *a << std::endl;
  } */
  
  std::cout<<"sdf read"<<std::endl;
  renderer.render(s);

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
/*   Window win{glm::ivec2{800,800}};
  
  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }

    auto t = win.get_time();
    auto m = win.mouse_position();
    win.update();
  }

  return 0;
} */
