#ifndef VECTOR_BASE_GUARD_HPP
#define VECTOR_BASE_GUARD_HPP

#include <SFML/Graphics.hpp>

namespace jt {

class vector2 final {
public:
    vector2()
        : m_vec { 0, 0 }
    {
    }
    vector2(float x, float y)
        : m_vec { x, y }
    {
    }

    vector2(sf::Vector2f const& v)
        : m_vec { v }
    {
    }

    ~vector2() = default;
    vector2(jt::vector2 const&) = default;
    vector2(jt::vector2&&) = default;

    vector2& operator=(jt::vector2 const&) = default;
    vector2& operator=(jt::vector2&&) = default;

    operator sf::Vector2f() const { return m_vec; }

    sf::Vector2f m_vec;

    float x() const { return m_vec.x; };
    float y() const { return m_vec.y; };

    float& x() { return m_vec.x; }
    float& y() { return m_vec.y; }
};

} // namespace jt

#endif
