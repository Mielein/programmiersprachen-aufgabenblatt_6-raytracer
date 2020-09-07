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
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"

class Renderer

{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render(Scene const& scene);
  Color trace(Ray const& ray, Scene const& scene);
  Color shade (std::shared_ptr<Shape> const& shape, Scene const& scene, Ray const& ray, HitPoint hit);
  Color tonemapping (Color const& clr);
  Color calculateAmbient(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit);
  Color claculateDiffuse(HitPoint const& hit, Scene const& scene, std::shared_ptr<Shape> const& shape);
  Color calculateSpecular(HitPoint const& hit);
  Color calculateReflection(HitPoint const& hit, int depth);  
  
  void write(Pixel const& p);  
  inline std::vector<Color> const& color_buffer() const     // was macht das hier? mal fragen nachher
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
};

#endif // #ifndef BUW_RENDERER_HPP