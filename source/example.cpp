#include "fensterchen.hpp"
#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <utility>
#include <cmath>


int main(int argc, char* argv[]){

  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./example.ppm";

  Renderer renderer{image_width, image_height, filename};

  std::cout<<"reading sdf"<<std::endl;
  Scene s = sdfParser("/home/marie/programmiersprachen-aufgabenblatt_6-raytracer/source/example.sdf");
  std::cout<<"sdf read"<<std::endl;
  renderer.render();

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
