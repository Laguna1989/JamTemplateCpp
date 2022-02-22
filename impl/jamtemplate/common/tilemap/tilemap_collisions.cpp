#include "tilemap_collisions.hpp"
#include <algorithm>
namespace jt {

void TilemapCollisions::add(jt::Rectf const& r) { m_rects.push_back(r); }

std::vector<jt::Rectf> const& TilemapCollisions::getRects() const { return m_rects; }

void TilemapCollisions::refineColliders()
{
    while (true) {
        auto changes = refineCollidersOneStep();
        if (!changes) {
            return;
        }
    }
}

bool TilemapCollisions::refineCollidersOneStep()
{
    std::vector<jt::Rectf> rects;
    // Note if this becomes a performance bottleneck, make treated a set instead of a vector.
    std::vector<jt::Rectf> treated;

    for (auto it1 = m_rects.cbegin(); it1 != m_rects.cend(); ++it1) {
        if (std::find(treated.cbegin(), treated.cend(), *it1) != treated.cend()) {
            continue;
        }
        for (auto it2 = it1; it2 != m_rects.cend(); ++it2) {
            if (it1 == it2) {
                continue;
            }

            if (std::find(treated.cbegin(), treated.cend(), *it2) != treated.cend()) {
                continue;
            }

            auto& r1 = *it1;
            auto& r2 = *it2;

            if (r1.width == r2.width && r1.left == r2.left && r2.top == r1.top + r1.height) {
                treated.push_back(r1);
                treated.push_back(r2);
                rects.push_back(jt::Rectf { r1.left, r1.top, r1.width, r1.height + r2.height });
                break;
            }
            if (r1.height == r2.height && r1.top == r2.top && r2.left == r1.left + r1.width) {
                treated.push_back(r1);
                treated.push_back(r2);
                rects.push_back(jt::Rectf { r1.left, r1.top, r1.width + r2.width, r1.height });
                break;
            }
        }
    }

    for (auto it1 = m_rects.cbegin(); it1 != m_rects.cend(); ++it1) {
        if (std::find(treated.cbegin(), treated.cend(), *it1) != treated.cend()) {
            continue;
        }
        rects.push_back(*it1);
    }
    bool const retval = (m_rects.size() != rects.size());
    m_rects = rects;
    return retval;
}

} // namespace jt
