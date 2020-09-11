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
#include "tools.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
  width_(w),
  height_(h),
  color_buffer_(w*h, Color{0.0, 0.0, 0.0}),
  filename_(file),
  ppm_(width_, height_){}
  
Renderer::Renderer(unsigned w, unsigned h, std::string const& file, unsigned depth):
  width_(w),
  height_(h),
  color_buffer_(w*h, Color{0.0, 0.0, 0.0}),
  filename_(file),
  ppm_(width_, height_),
  depth_(depth){}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene):
  width_(w),
  height_(h),
  color_buffer_(w*h, Color{0.0, 0.0, 0.0}),
  filename_(file),
  ppm_(width_, height_),
  scene_(scene){}


void sdf_render(){
  Scene s;
}

void Renderer::render(Scene const& scene){
/*   std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Hallo Marie, ich rendere jetzt was, okay?" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  /* std::size_t const checker_pattern_size = 20; */
/*   for (auto i : scene.shape_vec){
    std::cout << "Renderer 1: " << std::endl << *i << std::endl;
  }  */
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
        glm::vec3 origin = scene.camera_.pos_;
        float dir_x = scene.camera_.direction_.x + x-(width_*0.5f);
        float dir_y = scene.camera_.direction_.y + y-(height_*0.5f);
        float dir_z = scene.camera_.direction_.z + (width_/2.0f)/tan((scene.camera_.fovX/2.0f)*M_PI/180);
        glm::vec3 direction{dir_x,dir_y,-dir_z}; 

        glm::vec4 u = glm::vec4(glm::normalize(glm::cross(direction,scene.camera_.up_)),0.0f);
        glm::vec4 v = glm::vec4(glm::normalize(glm::cross({u.x,u.y,u.z},direction)),0.0f);
        glm::mat4 c{u,v,glm::vec4{glm::normalize(-direction),0},glm::vec4{origin,1}};
        Ray ray{origin, glm::normalize(direction)};
        glm::vec4 org = c*glm::vec4(ray.origin_,1.0f);
        glm::vec4 dir = c*glm::vec4(ray.direction_,0.0f);
        Ray c_ray{{org.x,org.y,org.z},{dir.x,dir.y,dir.z}};
        //Ray ray = scene.camera_.constructEyeRay(x,y,width_,height_);
        

/*      std::cout<<"origin \n";
        std::cout<<ray.origin.x<<"\n"<<ray.origin.y<<"\n"<<ray.origin.z<<std::endl;
        std::cout<<"direction \n";
        std::cout<<ray.direction.x<<"\n"<<ray.direction.y<<"\n"<<ray.direction.z<<std::endl; */
        Color color{0.0f,0.0f,0.0f};
        depth_ = 10;
        color = tonemapping(trace(c_ray,scene));
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
    auto t = i->intersect(ray);
    if (t.intersection_){
      if(t.name_ == "pusspuss"){ 
        std::cout << "hit" << std::endl;
      }
    }
    
/*     std::cout<<t.distance_<< std::endl;
    std::cout<<closest_t.distance_ << std::endl; */
    
    
    if(t.distance_< closest_t.distance_  && t.intersection_ ){
      closest_t = t;
      closest_o = i; 
    }
  }
  if(closest_o != nullptr){
      return tonemapping(shade(closest_o, scene, ray, closest_t));
    }
  return scene.background_.color_;
}

Color Renderer::shade (std::shared_ptr<Shape> const& shape,Scene const& scene, Ray const& ray, HitPoint hit){
  Color diffuse = claculateDiffuse(shape, scene, hit);
  Color ambient = calculateAmbient(shape, scene, hit);
  Color spec = calculateSpecular(shape, scene, hit);
  //Color reflect = calculateReflection(shape, scene, hit);

  Color shade{0.0f,0.0f,0.0f};
/* 
  if(shape->getMat()->mirror_ > 0 && hit.material_->op_ > 0){
    Color phong = (ambient + diffuse)*(1-shape->getMat()->mirror_)+reflect*shape->getMat()->mirror_+spec;
    shade = phong*(1-shape->getMat()->op_);
  }
  else if(shape->getMat()->mirror_ > 0){
    shade = (ambient + diffuse)*(1-shape->getMat()->mirror_)+reflect*shape->getMat()->mirror_ + spec; 
  }
  else{ */
    shade = ambient + diffuse + spec;
  //}
  return shade;
}

Color Renderer::tonemapping (Color const& clr){
  Color color{0.0f,0.0f,0.0f};
  color.r = clr.r / (clr.r + 1.0f);
  color.g = clr.g / (clr.g + 1.0f);
  color.b = clr.b / (clr.b + 1.0f);
  return color;
}

Color Renderer::calculateAmbient(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit){
  /* Color ambientLight{scene.background_.color_}; */
  Color ka = shape->getMat()->ka_;
  Color ambient_color = scene.background_.color_;  
  //std::cout << ka;
  //std::cout << ambient_color;
  //std::cout << ka * ambient_color << std::endl;
  return {ka * scene.background_.color_};
}

Color Renderer::claculateDiffuse(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit){
  Color diffused_clr{0.0f,0.0f,0.0f};
  std::vector<Color> result;

  for(auto light : scene.light_vec){
    bool obstacle = false;
    HitPoint light_hit;

    glm::vec3 vec_lights{light->pos_ - hit.intersect_pt_};
    Ray ray_lights{hit.intersect_pt_ + 0.1f * hit.normal_,glm::normalize(vec_lights)}; 
    
    for(auto i : scene.shape_vec){
      if(i == shape){
        continue;
      }
      else{
        light_hit = i->intersect(ray_lights);
        // erstmal unwichtig  std::cout << i->intersect(ray_lights).intersect_pt_.x << " " << i->intersect(ray_lights).intersect_pt_.y << " " << i->intersect(ray_lights).intersect_pt_.z << std::endl;
        if(light_hit.intersection_){
          obstacle = true;
          break;
        }
      }
    }

    if(!obstacle){
        Color ip{light->color_*light->brightness_};
        Color kd = shape->getMat()->kd_;
        float cross_prod = -(glm::dot(hit.normal_,glm::normalize(vec_lights)));
        cross_prod = std::max(cross_prod, 0.0f);
        cross_prod = glm::clamp(cross_prod, 0.0f, 1.0f);
        result.push_back({(ip*kd)*cross_prod});
    }
  }
  for(auto clr : result){  
    Color clamp_clr = clamping(clr);
    diffused_clr += clamp_clr;
  } 
  return diffused_clr;
}

Color Renderer::calculateSpecular(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit){
  Color spec_clr{0.0f,0.0f,0.0f};
  std::vector<Color> calc_clrs;

  for(auto light : scene.light_vec){
    bool obstacle = false;
    HitPoint light_hit;
    
    glm::vec3 vec_lights{light->pos_ - hit.intersect_pt_};
    Ray ray_lights{hit.intersect_pt_ + 0.1f * hit.normal_,glm::normalize(vec_lights)}; //checks if obstacle is between Light and intersection

    for(auto i : scene.shape_vec){
      if(i == shape){
        continue;
      }
      else{
        light_hit = i->intersect(ray_lights);
        if(light_hit.intersection_){
          obstacle = true;
          break;
        }
      }
    }

    if(!obstacle){
      float m = shape->getMat()->m_;
      glm::vec3 r = 2.0f*glm::dot(hit.normal_,glm::normalize(vec_lights))*hit.normal_-glm::normalize(vec_lights); //glm::dot -> Skalarprodukt
      glm::vec3 v = glm::normalize(scene.camera_.pos_ - hit.intersect_pt_);
      float cross_prod = glm::dot(r,v);
      cross_prod = std::max(cross_prod, 0.0f);
      if(cross_prod < 0){
        cross_prod = -cross_prod;}
      Color ks = shape->getMat()->ks_;
      Color ip{light->color_*light->brightness_};
      float cos = pow(cross_prod,m);
      float m_2 = (m+2)/(2*M_PI);
      calc_clrs.push_back({((ks*ip)*cos)*m_2});      
    }  
  }

  for(auto clr : calc_clrs){
    Color clamp_clr = {clamping(clr)};
    spec_clr += clamp_clr;
  }  
  return spec_clr;
}


Color Renderer::calculateReflection(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit){  
  glm::vec3 reflect_vec = glm::reflect(hit.intersect_direction_, hit.normal_);
  Ray reflect_ray{hit.intersect_pt_,glm::normalize(reflect_vec)};
  HitPoint next_hit;
  float depth = depth_;

  for(auto i : scene.shape_vec){
    next_hit = i->intersect(reflect_ray);
    if(next_hit.intersection_){
      if(depth > 0){
        for(int j = 0; j < depth; ++j){
          Color clr = calculateReflection(i,scene,next_hit);
          depth-=1;
          return clr;
        }
      }
      else{
        return {0.0f,0.0f,0.0f};
      }
    }
    return {1.0f,1.0f,1.0f};
  }
  
/*   printVec(reflect_vec); */


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

Renderer sdf_render(std::string const& filename){
  Scene output = sdfParser(filename);
  std::cout << std::endl;
  Renderer tmp = {output.render_value.w, output.render_value.h, output.render_value.file, output.render_value.depth};
  tmp.render(output);
  return tmp;
}
