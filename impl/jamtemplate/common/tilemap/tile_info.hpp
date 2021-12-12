#ifndef GUARD_JAMTEMPLATE_TILE_HPP
#define GUARD_JAMTEMPLATE_TILE_HPP

#include "vector.hpp"

namespace jt {

namespace tilemap {
struct TileInfo {
    jt::Vector2f position { 0.0f, 0.0f };
    jt::Vector2f size { 0.0f, 0.0f };
    int id { -1 };
};

} // namespace tilemap

} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILE_HPP
