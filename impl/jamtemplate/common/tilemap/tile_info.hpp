#pragma once

#include <vector.hpp>

namespace jt {

namespace tilemap {
struct TileInfo {
    jt::Vector2f position { 0.0f, 0.0f };
    jt::Vector2f size { 0.0f, 0.0f };
    int id { -1 };
};

} // namespace tilemap

} // namespace jt
