#ifndef GUARD_JAMTEMPLATE_RECT_HPP
#define GUARD_JAMTEMPLATE_RECT_HPP

#include "Vector.hpp"
#include <string>

namespace jt {
struct InfoRect {
    Vector2 position;
    Vector2 sizeDiagonal;
    float rotation;
    std::string type;
};
} // namespace jt
#endif
