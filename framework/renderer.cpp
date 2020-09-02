// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <memory>
#include <glm/glm.hpp>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
  width_(w),
  height_(h),
  color_buffer_(w*h, Color{0.0, 0.0, 0.0}),
  filename_(file),
  ppm_(width_, height_){}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene):
  width_(w),
  height_(h),
  color_buffer_(w*h, Color{0.0, 0.0, 0.0}),
  filename_(file),
  ppm_(width_, height_),
  scene_(scene){}


void Renderer::render(Scene const& scene){
  /* std::size_t const checker_pattern_size = 20; */

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
/*       if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      } */
      glm::vec3 origin{0,0,0};
      glm::vec3 direction = glm::normalize(glm::vec3{(x-width_/2.0f),(y-height_/2.0f),-(width_/2)/tan(scene.camera_.fovX/2*M_PI/180)});
      Ray ray{origin,{/* direction */ 0.0,0.0,-1.0}};
      if(p.x == 42 && p.y == 42){
        std::cout<<"origin \n";
        std::cout<<ray.origin.x<<"\n"<<ray.origin.y<<"\n"<<ray.origin.z<<std::endl;
        std::cout<<"direction \n";
        std::cout<<ray.direction.x<<"\n"<<ray.direction.y<<"\n"<<ray.direction.z<<std::endl;
      }
      Color colour{0.0,0.0,0.0};
      colour = trace(ray,scene);
      p.color = colour;
      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::trace(Ray const& ray, Scene const& scene){
  HitPoint closest_t;
  std::shared_ptr<Shape> closest_o = nullptr;
  for(auto i : scene.shape_vec){ 
    auto t = i->intersect(ray);
    if(glm::length(t.intersect_pt_-ray.origin)<glm::length(closest_t.intersect_pt_-ray.origin)){
      closest_t = t;
      closest_o = i; 
    }  
  }
  if(closest_o != nullptr){
    std::cout << closest_t.distance_ << std::endl;
    return shade(scene,ray, closest_t);
  }
  else{
    return scene.background_.colour_;
  }

  //(TO-DO)
}
Color Renderer::shade (Scene const& scene, Ray const& ray, HitPoint hit){
  Color ambientLight{0.0f,0.0f,0.0f};
  for(auto shapes : scene.shape_vec){
    ambientLight = shapes->getMat()->ka_ * scene.background_.colour_;
  }

  //TO-DO
}




Color Renderer::tonemapping (Color const& clr){
  Color colour{0.0f,0.0f,0.0f};
  colour.r = clr.r / (clr.r + 1.0f);
  colour.g = clr.g / (clr.g + 1.0f);
  colour.b = clr.b / (clr.b + 1.0f);
  return colour;
}
Color Renderer::calculateAmbient(HitPoint const& hit){
  Color ambient = scene_.background_.colour_;
  Color ka = hit.material_->ka_;
  return {ambient.r*ka.r,ambient.g*ka.g,ambient.b*ka.b};
}
Color Renderer::claculateDiffuse(HitPoint const& hit){
  Color diffused_clr{0.0f,0.0f,0.0f};
  std::vector<Color> calc_clrs;
  
  for(auto light : scene_.light_vec){
    bool obstacle = false;

    HitPoint hit;
    glm::vec3 vec_lights = glm::normalize(light->pos_ - hit.intersect_pt_);
    Ray ray_lights{hit.intersect_pt_+0.1f*hit.normal_,vec_lights}; //checks if obstacle is between Light and intersection

    for(std::shared_ptr<Shape> const& shapes : scene_.shape_vec){
      if(hit.intersection_){
        obstacle = true;
      }
      if(!obstacle){
        Color ip{light->colour_.r*light->brightness_,light->colour_.g*light->brightness_,light->colour_.b*light->brightness_};
        Color kd = hit.material_->kd_;
        float cross_prod = glm::dot(vec_lights,glm::normalize(hit.normal_));
        calc_clrs.push_back({kd.r*cross_prod*ip.r,kd.g*cross_prod*ip.g,kd.b*cross_prod*ip.b});
      }
    }
    for(auto clr : calc_clrs){
      diffused_clr += clr;
    }
    return diffused_clr;

  }
  //TO-DO
}
Color Renderer::calculateReflection(HitPoint const& hit, int depth){
  //TO-DO
}
Color Renderer::calculateSpecular(HitPoint const& hit){
  //TO-DO
}

void Renderer::write(Pixel const& p){
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }
  ppm_.write(p);
}
