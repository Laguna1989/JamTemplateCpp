#include "tilemap_collisions.hpp"
#include <algorithm>

namespace jt {

namespace {
int getEntry(std::vector<int> const& vec, int x, int y, int width)
{
    auto idx = x + y * width;
    if (idx >= vec.size()) {
        return false;
    }
    return vec[idx];
}

void setEntry(std::vector<int>& vec, int x, int y, int width, int value)
{
    auto idx = x + y * width;
    vec[idx] = value;
}
} // namespace

void TilemapCollisions::add(jt::Rectf const& r) { m_rects.push_back(r); }

std::vector<jt::Rectf> const& TilemapCollisions::getRects() const { return m_rects; }

void TilemapCollisions::refineColliders(float size)
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

bool TilemapCollisions::refineCollidersOneStep()
{
    std::vector<jt::Rectf> rects;
    // Note if this becomes a performance bottleneck, make treated a set instead of a vector.
    std::vector<jt::Rectf> treated;

    rects.reserve(m_rects.size());

    for (auto it1 = m_rects.cbegin(); it1 != m_rects.cend(); ++it1) {
        if (std::count(treated.cbegin(), treated.cend(), *it1) != 0) {
            continue;
        }
        for (auto it2 = it1; it2 != m_rects.cend(); ++it2) {
            if (it1 == it2) {
                continue;
            }

            if (std::count(treated.cbegin(), treated.cend(), *it2) != 0) {

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
        if (std::count(treated.cbegin(), treated.cend(), *it1) != 0) {
            continue;
        }
        rects.push_back(*it1);
    }
    bool const retval = (m_rects.size() != rects.size());
    m_rects = rects;
    return retval;
}

} // namespace jt
