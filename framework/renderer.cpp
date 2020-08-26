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


void Renderer::render(){
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::trace(Ray const& ray, Scene const& scene, int depth){
/*   HitPoint closest_t;
  HitPoint closest_o;
  for(auto i : scene.shape_vec){ 
    auto t = i->intersect(ray);
    if(glm::length(t.intersect_pt_-ray.origin)<glm::length(closest_t.intersect_pt_-ray.origin)){
      closest_t = t;
      //closest_o = *i; 
    }  
  }
  if(closest_o != nullptr){
        return shade(scene,ray, closest_t, );
      }
      else{
        return;
      } */
       
    
 
  //TO-DO
}
Color Renderer::shade (Scene const& scene, Ray const& ray, HitPoint hit){
  //TO-DO
}
Color Renderer::tonemapping (Color const& clr){
  //TO-DO
}
Color Renderer::calculateAmbient(HitPoint const& hit){
  Color ambient = scene_.background_.colour_;
  Color ka = hit.material_->ka_;
  return {ambient.r*ka.r,ambient.g*ka.g,ambient.b*ka.b};
}
Color Renderer::claculateDiffuse(HitPoint const& hit){
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
