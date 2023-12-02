#include "ease_from_points.hpp"
#include <algorithm>
#include <stdexcept>

jt::EaseFromPoints::EaseFromPoints(std::deque<jt::Vector2f> const& vec)
    : m_points { vec }
{
    std::sort(
        m_points.begin(), m_points.end(), [](auto const& a, auto const& b) { return a.x < b.x; });
    if (m_points.empty()) {
        throw std::invalid_argument { "EaseFromPoints with no points." };
    }
    if (m_points.front().x != 0.0f) {
        m_points.push_front(jt::Vector2f { 0.0f, m_points.front().y });
    }
    if (m_points.back().x != 1.0f) {
        m_points.push_back(jt::Vector2f { 1.0f, m_points.back().y });
    }
}

float jt::EaseFromPoints::easeIn(float t, float minY, float maxY) const
{
    auto const diffY = maxY - minY;
    if (t <= 0.0f) {
        return m_points.front().y * diffY + minY;
    }
    if (t >= 1.0f) {
        return m_points.back().y * diffY + minY;
    }

    auto it1 = m_points.cbegin();
    while (it1->x <= t) {
        it1++;
    }
    auto const it2 = it1;

    it1--;
    auto const totalT = it2->x - it1->x;
    auto const relT = (t - (it1->x)) / totalT;

    return minY + (relT * it2->y + (1.0f - relT) * it1->y) * (maxY - minY);
}
