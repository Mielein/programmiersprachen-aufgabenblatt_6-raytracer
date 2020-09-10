#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

//now single threaded again
int main(int argc, char* argv[])
{

  //renderer.render();
  Renderer scene = sdf_render("../../source/example.sdf");
  

  Window window{{scene.get_width(), scene.get_height()}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();      
    }
    //window.show(renderer.color_buffer());
    window.show(scene.color_buffer());
  }

  return 0;
}
