#ifndef GUARD_JAMTEMPLATE_TILEMAP_COLLISIONS_HPP
#define GUARD_JAMTEMPLATE_TILEMAP_COLLISIONS_HPP

#include "rect.hpp"
#include <vector>

namespace jt {

class TilemapCollisions {
public:
    void add(jt::Rectf const& r);

    std::vector<jt::Rectf> const& getRects() const;

    void refineColliders(float size);

private:
    std::vector<jt::Rectf> m_rects {};
    bool refineCollidersOneStep();
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILEMAP_COLLISIONS_HPP
