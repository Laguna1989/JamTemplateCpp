#ifndef RECT_INCLUDEGUARD
#define RECT_INCLUDEGUARD

#include "vector.hpp"
#include <string>

struct Rect {
    jt::vector2 position;
    jt::vector2 sizeDiagonal;
    float rotation;
    std::string m_type;
};

#endif
