#ifndef GUARD_JAMTEMPLATE_RECT_HPP
#define GUARD_JAMTEMPLATE_RECT_HPP

#include "vector.hpp"
#include <string>

namespace jt {
struct InfoRect {
    Vector2 position { 0.0f, 0.0f };
    Vector2 size { 0.0f, 0.0f };
    float rotation { 0.0f };
    std::string type { "" };
    std::string name { "" };
};
} // namespace jt
#endif
