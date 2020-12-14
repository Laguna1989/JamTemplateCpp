#ifndef GUARD_JAMTEMPLATE_RECT_HPP
#define GUARD_JAMTEMPLATE_RECT_HPP

#include "vector.hpp"
#include <string>

struct InfoRect {
    jt::Vector2 position;
    jt::Vector2 sizeDiagonal;
    float rotation;
    std::string m_type;
};

#endif
