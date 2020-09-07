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
/*   for (auto i : scene.shape_vec){
    std::cout << "Renderer 1: " << std::endl << *i << std::endl;
  } */
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
/*    if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } 
      else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      } */
        glm::vec3 origin = scene.camera_.pos_;
        float dir_x = scene.camera_.direction_.x + x-(width_*0.5f);
        float dir_y = scene.camera_.direction_.y + y-(height_*0.5f);
        float dir_z = scene.camera_.direction_.z + (width_/2.0f)/tan((scene.camera_.fovX/2.0f)*M_PI/180);
        glm::vec3 direction{dir_x,dir_y,-dir_z}; 
        //Ray ray = scene.camera_.constructEyeRay(x,y,width_,height_);
        Ray ray{origin, glm::normalize(direction)};
/*      std::cout<<"origin \n";
        std::cout<<ray.origin.x<<"\n"<<ray.origin.y<<"\n"<<ray.origin.z<<std::endl;
        std::cout<<"direction \n";
        std::cout<<ray.direction.x<<"\n"<<ray.direction.y<<"\n"<<ray.direction.z<<std::endl; */
        Color color{0.0,0.0,0.0};
        color = trace(ray,scene);
        p.color = color;
        write(p);

    }
  }
  ppm_.save(filename_);
}

Color Renderer::trace(Ray const& ray, Scene const& scene){
  HitPoint closest_t;
  std::shared_ptr<Shape> closest_o = nullptr;
  for(auto i : scene.shape_vec){ 
    //std::cout << *i << std::endl;
    auto t = i->intersect(ray);
    if (t.name_ == "jucyButt"){ 
      std::cout << t.name_ << std::endl;
    }
    
/*     std::cout<<t.distance_<< std::endl;
    std::cout<<closest_t.distance_ << std::endl; */
    
    
    if(t.distance_< closest_t.distance_  && t.intersection_ ){
      closest_t = t;
      closest_o = i; 
/*       std::cout<<closest_t.name_; */
    }
  }
  if(closest_o != nullptr){
      return tonemapping(shade(closest_o, scene, ray, closest_t));
    }
  return scene.background_.color_;
}

Color Renderer::shade (std::shared_ptr<Shape> const& shape,Scene const& scene, Ray const& ray, HitPoint hit){
/*   Ray shadowRay;
  glm::vec3 v;
  glm::vec3 l;
  bool shade = false;
  Color result = calculateAmbient(shape, scene, hit);
  for(auto i : scene.light_vec){ 
    shadowRay.origin_ = hit.intersect_pt_;
    shadowRay.direction_ = i->pos_ - hit.intersect_pt_ ;
    if(shade == true){
      l = glm::normalize(i->pos_ - hit.intersect_pt_);
      v = -(glm::normalize(ray.direction_));
    }
    return {0.0f,0.0f,0.0f};
  } */
  
  return claculateDiffuse(hit, scene, shape) + calculateAmbient(shape, scene, hit) + calculateSpecular(hit);

}

Color Renderer::tonemapping (Color const& clr){
  Color color{0.0f,0.0f,0.0f};
  color.r = clr.r / (clr.r + 1.0f);
  color.g = clr.g / (clr.g + 1.0f);
  color.b = clr.b / (clr.b + 1.0f);
  return color;
}

Color Renderer::calculateAmbient(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit){
  Color ambientLight{shape->getMat()->ka_ * scene.background_.color_};
  return {ambientLight};
}

Color Renderer::claculateDiffuse(HitPoint const& hit, Scene const& scene, std::shared_ptr<Shape> const& shape){
  Color diffused_clr{0.0f,0.0f,0.0f};
  std::vector<Color> calc_clrs;

  for(auto light : scene_.light_vec){
    bool obstacle = true;
    HitPoint light_hit;
    
    glm::vec3 vec_lights = glm::normalize(light->pos_ - hit.intersect_pt_);
    Ray ray_lights{hit.intersect_pt_ + 0.1f * hit.normal_,vec_lights}; //checks if obstacle is between Light and intersection
    for(auto i : scene_.shape_vec){
      light_hit = i->intersect(ray_lights);
      
      for(std::shared_ptr<Shape> const& shapes : scene_.shape_vec){
        if(hit.intersection_){
          obstacle = true;
        }
        if(!obstacle){
          Color ip{light->color_.r*light->brightness_,light->color_.g*light->brightness_,light->color_.b*light->brightness_};
          Color kd = hit.material_->kd_;
          float cross_prod = glm::dot(vec_lights,glm::normalize(hit.normal_));
          calc_clrs.push_back({kd.r*cross_prod*ip.r,kd.g*cross_prod*ip.g,kd.b*cross_prod*ip.b});
        }
      }
    }  
    for(auto clr : calc_clrs){
      diffused_clr += clr;
    }  

  }
  return diffused_clr;
}
Color Renderer::calculateReflection(HitPoint const& hit, int depth){
  
}

Color Renderer::calculateSpecular(HitPoint const& hit){
  Color spec_clr{0.0f,0.0f,0.0f};
  std::vector<Color> calc_clrs;

for(auto light : scene_.light_vec){
    bool obstacle = false;
    HitPoint hit;
    
    glm::vec3 vec_lights = glm::normalize(light->pos_ - hit.intersect_pt_);
    Ray ray_lights{hit.intersect_pt_+0.1f*hit.normal_,vec_lights}; //checks if obstacle is between Light and intersection
    for(auto i : scene_.shape_vec){
      hit = i->intersect(ray_lights);
    
      for(std::shared_ptr<Shape> const& shapes : scene_.shape_vec){
        if(hit.intersection_){
          obstacle = true;
        }
        if(!obstacle){
          float m = hit.material_->m_;
          glm::vec3 r = 2.0f*glm::dot(hit.normal_,vec_lights)*hit.normal_-vec_lights; //glm::dot -> Skalarprodukt
          glm::vec3 v = glm::normalize(scene_.camera_.pos_ - hit.intersect_pt_);

          float cross_prod = glm::dot(r,v);

          if(cross_prod < 0){
            cross_prod = -cross_prod;
          }
          Color ks = hit.material_->ks_;
          Color ip{light->color_.r*light->brightness_,light->color_.g*light->brightness_,light->color_.b*light->brightness_};
          float cos = pow(cross_prod,m);
          float m_2 = (m+2)/(2*M_PI);
          calc_clrs.push_back({ks.r*ip.r*cos*m_2,ks.g*ip.g*cos*m_2,ks.b*ip.b*cos*m_2});
        }
      }
    }  
    for(auto clr : calc_clrs){
      spec_clr += clr;
    }  

  }
  return spec_clr;
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
