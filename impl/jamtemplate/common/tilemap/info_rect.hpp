#ifndef GUARD_JAMTEMPLATE_RECT_HPP
#define GUARD_JAMTEMPLATE_RECT_HPP

#include "vector.hpp"
#include <map>
#include <string>

namespace jt {

namespace tilemap {

struct InfoRectProperties {
    std::map<std::string, bool> bools;
    std::map<std::string, float> floats;
    std::map<std::string, int> ints;
    std::map<std::string, std::string> strings;
};

struct InfoRect {
    jt::Vector2f position { 0.0f, 0.0f };
    jt::Vector2f size { 0.0f, 0.0f };
    float rotation { 0.0f };
    std::string type { "" };
    std::string name { "" };
    InfoRectProperties properties {};
};

} // namespace tilemap
} // namespace jt
#endif
