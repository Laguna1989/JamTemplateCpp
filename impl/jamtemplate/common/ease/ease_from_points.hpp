#ifndef JAMTEMPLATE_EASE_FROM_POINTS_HPP
#define JAMTEMPLATE_EASE_FROM_POINTS_HPP

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

#endif // JAMTEMPLATE_EASE_FROM_POINTS_HPP
