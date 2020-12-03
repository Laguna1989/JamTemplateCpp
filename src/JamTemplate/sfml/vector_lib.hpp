#ifndef GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP

#include "vector_base.hpp"
#include <SFML/System/Vector2.hpp>

namespace jt {

class vector2 final : public vector2Base {
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

    float x() const override { return m_vec.x; };
    float y() const override { return m_vec.y; };

    float& x() override { return m_vec.x; }
    float& y() override { return m_vec.y; }

private:
    sf::Vector2f m_vec;
};

class vector2u final : public vector2uBase {
public:
    vector2u()
        : m_vec { 0, 0 }
    {
    }
    vector2u(unsigned int x, unsigned int y)
        : m_vec { x, y }
    {
    }

    vector2u(sf::Vector2u const& v)
        : m_vec { v }
    {
    }

    ~vector2u() = default;
    vector2u(jt::vector2u const&) = default;
    vector2u(jt::vector2u&&) = default;

    jt::vector2u& operator=(jt::vector2u const&) = default;
    jt::vector2u& operator=(jt::vector2u&&) = default;

    operator sf::Vector2u() const { return m_vec; }

    sf::Vector2u m_vec;

    unsigned int x() const override { return m_vec.x; };
    unsigned int y() const override { return m_vec.y; };

    unsigned int& x() override { return m_vec.x; }
    unsigned int& y() override { return m_vec.y; }
};

} // namespace jt

#endif
