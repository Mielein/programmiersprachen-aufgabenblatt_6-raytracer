#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>
#include <iostream>

struct Material{
    Material(){};

    Material(std::string name, Color const& ks, Color const& kd, Color const& ka, float m):
        name_{name},
        ks_{ks},
        kd_{kd},
        ka_{ka},
        m_{m}{};

std::string name_{"default"};
Color ks_{0.0f,0.0f,0.0f};
Color kd_{0.0f,0.0f,0.0f};
Color ka_{0.0f,0.0f,0.0f};
float m_ = 1.0f;
};

#endif