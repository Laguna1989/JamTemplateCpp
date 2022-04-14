#include "tilemap_collisions.hpp"
#include <algorithm>
#include <cassert>

namespace {
int getEntry(std::vector<int> const& vec, int x, int y, int width)
{
    auto idx = x + y * width;
    assert(static_cast<unsigned>(idx) < vec.size());

    return vec[idx];
}

void setEntry(std::vector<int>& vec, int x, int y, int width, int value)
{
    auto idx = x + y * width;
    assert(static_cast<unsigned>(idx) < vec.size());
    vec[idx] = value;
}

} // namespace

void jt::TilemapCollisions::add(jt::Rectf const& r) { m_rects.push_back(r); }

std::vector<jt::Rectf> const& jt::TilemapCollisions::getRects() const { return m_rects; }

void jt::TilemapCollisions::refineColliders(float size)
{
    if (m_rects.empty()) {
        return;
    }
    int const xmin
        = static_cast<int>(std::min_element(m_rects.cbegin(), m_rects.cend(),
                               [](auto const& r1, auto const& r2) { return r1.left < r2.left; })
                               ->left
            / size);

    int const ymin
        = static_cast<int>(std::min_element(m_rects.cbegin(), m_rects.cend(),
                               [](auto const& r1, auto const& r2) { return r1.top < r2.top; })
                               ->top
            / size);

    int const xmax
        = static_cast<int>(std::max_element(m_rects.cbegin(), m_rects.cend(),
                               [](auto const& r1, auto const& r2) { return r1.left < r2.left; })
                               ->left
            / size);

    int const ymax
        = static_cast<int>(std::max_element(m_rects.cbegin(), m_rects.cend(),
                               [](auto const& r1, auto const& r2) { return r1.top < r2.top; })
                               ->top
            / size);

    std::vector<int> lookup;
    lookup.resize(static_cast<std::size_t>(xmax + 1) * (ymax + 1));
    for (auto const& r : m_rects) {
        setEntry(
            lookup, static_cast<int>(r.left / size), static_cast<int>(r.top / size), xmax + 1, 1);
    }

    std::vector<jt::Rectf> rects;
    for (auto y = ymin; y < ymax + 1; ++y) {
        for (auto x = xmin; x < xmax + 1; ++x) {
            if (x > xmax) {
                break;
            }
            if (!getEntry(lookup, x, y, xmax + 1)) {
                continue;
            }
            int xpeek = x;
            while (getEntry(lookup, xpeek, y, xmax + 1)) {
                xpeek++;
                if (xpeek >= xmax + 1) {
                    break;
                }
            }
            for (auto xwrite = x; xwrite != xpeek; ++xwrite) {
                setEntry(lookup, xwrite, y, xmax + 1, 0);
            }
            setEntry(lookup, x, y, xmax + 1, xpeek - x);

            x = xpeek;
        }
    }
    for (auto x = xmin; x < xmax + 1; ++x) {
        for (auto y = ymin; y < ymax + 1; ++y) {
            if (y > ymax) {
                break;
            }
            auto currentValue = getEntry(lookup, x, y, xmax + 1);
            if (currentValue == 0) {
                continue;
            }
            int ypeek = y;
            while (getEntry(lookup, x, ypeek, xmax + 1) == currentValue) {
                ypeek++;
                if (ypeek >= ymax + 1) {
                    break;
                }
            }
            rects.emplace_back(
                jt::Rectf { x * size, y * size, currentValue * size, (ypeek - y) * size });
            y = ypeek - 1;
        }
    }

    m_rects = rects;
}
