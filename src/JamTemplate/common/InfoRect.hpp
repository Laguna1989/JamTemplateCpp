#ifndef GUARD_JAMTEMPLATE_RECT_HPP
#define GUARD_JAMTEMPLATE_RECT_HPP

#include "vector.hpp"
#include <string>

struct InfoRect {
    jt::vector2 position;
    jt::vector2 sizeDiagonal;
    float rotation;
    std::string m_type;
};

#endif
