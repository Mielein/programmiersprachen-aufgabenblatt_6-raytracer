// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>
#include <glm/glm.hpp>

struct Color
{

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator*=(Color const& other)
  {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
  }

  Color& operator*=(float const& other)
  {
    r *= other;
    g *= other;
    b *= other;
    return *this;
  }  

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*(Color const& other){
    r*other.r;
    g*other.g;
    b*other.b;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  float r;
  float g;
  float b;

  friend Color operator*(Color const& a, Color const& b){    
    auto tmp(a);
    tmp *= b;
    return tmp;
  }
  
  friend Color operator*(Color const& a, float const& b){
    auto tmp(a);
    tmp *= b;
    return tmp;
  }

  friend Color clamping(Color const& a){
    return {glm::clamp(a.r,0.0f,1.0f),glm::clamp(a.g,0.0f,1.0f),glm::clamp(a.b,0.0f,1.0f)};
  }

};

#endif //#define BUW_COLOR_HPP
