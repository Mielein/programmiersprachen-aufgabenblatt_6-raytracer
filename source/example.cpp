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
  Material green {"Green", {0.0f,1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}, 0.0f};
  Material orange {"Orange", {1.0f,0.65f,0.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}, 0.0f};
  Material random {"random", {0.815f,0.815f,0.815f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}, 0.0f};
  std::shared_ptr<Material> green_ptr = std::make_shared<Material>(green);
  std::shared_ptr<Material> orange_ptr = std::make_shared<Material>(orange);
  std::shared_ptr<Material> random_ptr = std::make_shared<Material>(random);
  mat_map.insert(std::make_pair("Green", green_ptr));
  mat_map.insert(std::make_pair("Orange", orange_ptr));
  mat_map.insert(std::make_pair("Random", random_ptr));

  Sphere sphere1{"pussy",{0.0f,0.0f,1.0f}, green_ptr,{0.0f,0.0f,-100.0f}, 5.0f};
  Sphere sphere2{"pimpim",{1.0f,0.0f,0.0f}, orange_ptr,{0.0f,7.5f,-100.0f}, 5.0f};
  Box box1{{-10.0f,-10.0f,-150.0f},{5.0f,5.0f,-96.0f},"jucyButt",{0.0f,0.0f,0.0f},random_ptr};
  std::shared_ptr<Shape>spheres1 = std::make_shared<Sphere>(sphere1);
  std::shared_ptr<Shape>spheres2 = std::make_shared<Sphere>(sphere2);
  std::shared_ptr<Shape>boxes1 = std::make_shared<Box>(box1);
  shape_vec.push_back(spheres1);
  shape_vec.push_back(spheres2);
  shape_vec.push_back(boxes1);

  for(auto i : shape_vec){
    std::cout << i << "\n" << std::endl;
  }

  Light light{};
  std::shared_ptr<Light>lights = std::make_shared<Light>(light);
  light_vec.push_back(lights);
  Camera cam{};
  Ambient amby{"a",{1.0,0.2,1.4}};
  Scene s{shape_vec,light_vec,mat_map,cam,amby};
  /* sdfParser("/home/marie/programmiersprachen-aufgabenblatt_6-raytracer/source/example.sdf"); */

    for (auto a : s.shape_vec){
    std::cout<< *a << std::endl;
  }
  
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
