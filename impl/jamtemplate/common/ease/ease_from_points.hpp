#pragma once

#include <vector.hpp>
#include <deque>

namespace jt {
class EaseFromPoints {
public:
    explicit EaseFromPoints(std::deque<jt::Vector2f> const& vec);
    float easeIn(float t, float minY, float maxY) const;

private:
    std::deque<jt::Vector2f> m_points;
};
} // namespace jt
