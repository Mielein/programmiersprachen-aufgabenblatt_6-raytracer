#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>
#include <iostream>

struct Material{
    Material(){};

    Material(std::string name, Color const& ka, Color const& kd, Color const& ks, float m, float op, float mirror):
        name_{name},
        ka_{ka},
        kd_{kd},
        ks_{ks},
        m_{m},
        op_{glm::clamp(0.0f,0.0f,1.0f)},
        mirror_{mirror}{};

std::string name_{"default"};
Color ka_{0.0f,0.0f,0.0f};
Color kd_{0.0f,0.0f,0.0f};
Color ks_{0.0f,0.0f,0.0f};
float m_ = 1.0f;
float op_ = 0.0f;
float mirror_ = 0.0f;
};

#endif