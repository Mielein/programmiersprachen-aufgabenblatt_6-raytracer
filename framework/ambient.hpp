#ifndef AMBIENT_HPP
#define AMBIENT_HPP
#include "color.hpp"

struct Ambient{
    Color colour_;

    Ambient(Color colour):
        colour_(colour){};
};



#endif