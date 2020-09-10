// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"
#include <string>
#include <glm/glm.hpp>
#include "render.hpp"


class Renderer

{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(unsigned w, unsigned h, std::string const& file, unsigned depth);
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene, unsigned depth);

  void render(Scene const& scene);
  void sdf_render();
  Color trace(Ray const& ray, Scene const& scene);
  Color shade (std::shared_ptr<Shape> const& shape, Scene const& scene, Ray const& ray, HitPoint hit);
  Color tonemapping (Color const& clr);
  Color calculateAmbient(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit);
  Color claculateDiffuse(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit);
  Color calculateSpecular(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit);
  Color calculateReflection(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit, unsigned depth);  
  
  void write(Pixel const& p);  
  inline std::vector<Color> const& color_buffer() const 
  {
    return color_buffer_;
  }

private:

  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
  Scene scene_;
  unsigned depth_;
};

#endif // #ifndef BUW_RENDERER_HPP