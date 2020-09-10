#include "../framework/fensterchen.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "shape.hpp"
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
  Material green {"Green", {0.65, 1.00, 0.75},{0.65, 1.00, 0.75},{0.65, 1.00, 0.75}, 2.0f, 0.0f};
  Material orange {"Orange", {0.26, 0.57, 0.97}, {0.26, 0.57, 0.97}, {0.26, 0.57, 0.97}, 5.0f, 0.0f};
  Material random {"random", {0.815f,0.815f,0.815f}, {0.815f,0.815f,0.815f}, {0.815f,0.815f,0.815f}, 10.0f, 0.0f};
  Material rand_pt_2 {"random_pt_2", {0.3f,0.67,0.7}, {0.3f,0.67,0.7}, {0.3f,0.67,0.7}, 15.0f, 0.0f};
  Material vanilla {"Vanille", {0.47, 0.66, 0.97}, {0.47, 0.66, 0.97}, {0.47, 0.66, 0.97}, 2.0f, 0.0f};

  std::shared_ptr<Material> green_ptr = std::make_shared<Material>(green);
  std::shared_ptr<Material> orange_ptr = std::make_shared<Material>(orange);
  std::shared_ptr<Material> random_ptr = std::make_shared<Material>(random);
  std::shared_ptr<Material> random2_ptr = std::make_shared<Material>(rand_pt_2);
  std::shared_ptr<Material> vanilla_ptr = std::make_shared<Material>(vanilla);


  mat_map.insert(std::make_pair("Green", green_ptr));
  mat_map.insert(std::make_pair("Orange", orange_ptr));
  mat_map.insert(std::make_pair("Random", random_ptr));
  mat_map.insert(std::make_pair("Random part 2", random2_ptr));
  mat_map.insert(std::make_pair("Vanille", vanilla_ptr));


  Sphere sphere1{"pussy",{0.0f,0.0f,1.0f}, green_ptr,{4.0f,-10.0f,-55.0f}, 7.0f};
  Sphere sphere2{"pimpim",{1.0f,0.0f,0.0f}, orange_ptr,{-15.0f,12.5f,-100.0f}, 5.0f};
  Sphere sphere3{"pullermann",{0.0f,1.0f,0.0f}, random_ptr,{10.0f,25.5f,-100.0f}, 5.0f};
  Box box1{{-10.0f, -15.0f,-70.0f},{-20.0f, -5.0f,-120.0f},"jucyButt",{0.0f,0.0f,0.0f},random_ptr};
  Box box2{{15.0f, -6.0f,-80.0f},{25.0f, 6.0f,-140.0f},"francesco",{0.0f,0.0f,0.0f},random2_ptr};
  Box box3{{40.0f, -30.0f,-200.0f},{-40.0f, 30.0f,-170.0f},"stinkyButt",{0.0f,0.0f,0.0f},vanilla_ptr};
  Triangle triangle1{"pusspuss",random2_ptr,{},{4.0f,-15.0f,-100.0f},{-15.0f,12.5f,-100.0f},{10.0f,25.5f,-100.0f}};
 
  std::shared_ptr<Shape>spheres1 = std::make_shared<Sphere>(sphere1);
  std::shared_ptr<Shape>spheres2 = std::make_shared<Sphere>(sphere2);
  std::shared_ptr<Shape>spheres3 = std::make_shared<Sphere>(sphere3);
  std::shared_ptr<Shape>boxes1 = std::make_shared<Box>(box1);
  std::shared_ptr<Shape>boxes2 = std::make_shared<Box>(box2);
  std::shared_ptr<Shape>boxes3 = std::make_shared<Box>(box3);

  //std::shared_ptr<Shape>triangles1 = std::make_shared<Triangle>(triangle1);


  //std::cout << " hier ist bullshit: "<<sphere1.getMat()->ka_ << std::endl;

  shape_vec.push_back(spheres1);
  shape_vec.push_back(spheres2);
  shape_vec.push_back(spheres3);
  shape_vec.push_back(boxes1);
  shape_vec.push_back(boxes2);
  shape_vec.push_back(boxes3);
  //shape_vec.push_back(triangles1);

  for(auto i : shape_vec){
    std::cout << i <<  "\n"<< std::endl;
    
  }

  Light light{"stinkyLight",{-100.0f, 100.0 ,0.0f}, {0.65f, 1.00f, 0.75f}, 2.0f};
  Light light2{"Essens of Life, lite",{100.0f, -50.0 ,0.0f}, {1.00f, 0.50f, 0.00f}, 2.0f};
  std::shared_ptr<Light>lights = std::make_shared<Light>(light);
  std::shared_ptr<Light>lights2 = std::make_shared<Light>(light2);
  light_vec.push_back(lights);
  light_vec.push_back(lights2);



  Camera cam{};
  Ambient amby{"a",{0.42, 0.1, 0.18}};
 // Scene s{shape_vec,light_vec, mat_map,  ,cam, amby}; 
  Scene scene = sdfParser("../../source/example.sdf"); 

  for (auto a : scene.light_vec){
    std::cout<< a->name_ << std::endl;
  }
  
  sdf_render("../../source/example.sdf");
  /* Ray test{{0.0f,0.0f,0.0f},{1.0f,0.0f,-1.0f}};
  test.transformRay(sphere1.getWorldInv()); */

/*   std::cout<<"sdf read"<<std::endl;*/
      //renderer.render(scene); 
       

/*   std::cout<<scene.background_.name_<<" ambient name"<<std::endl;
  std::cout<<scene.background_.color_.r<<" "<<scene.background_.color_.g<<" "<<scene.background_.color_.b<<" ambient colour"<<std::endl;
  std::cout<<scene.camera_.name_<<" camera name"<<std::endl;
  std::cout<<scene.camera_.pos_.x<<scene.camera_.pos_.y<<scene.camera_.pos_.z<<" camera pos"<<std::endl;
  std::cout<<scene.camera_.direction_.x<<scene.camera_.direction_.y<<scene.camera_.direction_.z<<" camera direction"<<std::endl;
  std::cout<<scene.camera_.fovX<< " camera fovX"<<std::endl;
  std::cout << std::endl;

  for(auto i : scene.light_vec){
    std::cout<<i->name_<<" light name"<<std::endl;
    std::cout<<i->pos_.x<<i->pos_.y<<i->pos_.z<<" light pos"<<std::endl;
    std::cout<<i->color_.r<<i->color_.g<<i->color_.b<<" light colour"<<std::endl;
    std::cout<<i->brightness_<<std::endl;
    std::cout << "" << std::endl;

  }
  std::cout << std::endl;

  for(auto i : scene.mat_map){
    std::cout<<i.first<<" first mat"<<std::endl;
    std::cout<<i.second->name_<<" mat name"<<std::endl;
    std::cout<<i.second->ka_<<" mat ka"<<std::endl;
    std::cout<<i.second->kd_<<" mat kd"<<std::endl;
    std::cout<<i.second->ks_<<" mat ks"<<std::endl;
    std::cout << "" << std::endl;

  } */
/*   for(auto i : scene.shape_vec){
    std::cout<<*i<<std::endl;
    std::cout << "" << std::endl;
  } */
/*   for(auto i : s.shape_vec){
    std::cout<<*i<<std::endl;
    std::cout << "" << std::endl;
  } */


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
