#ifndef GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP

#include "vector_base.hpp"
#include <SFML/System/Vector2.hpp>

namespace jt {

class Vector2 final : public Vector2Base {
public:
    Vector2()
        : m_vec { 0, 0 }
    {
    }
    Vector2(float x, float y)
        : m_vec { x, y }
    {
    }

    Vector2(sf::Vector2f const& v)
        : m_vec { v }
    {
    }

    ~Vector2() = default;
    Vector2(jt::Vector2 const&) = default;
    Vector2(jt::Vector2&&) = default;

    Vector2& operator=(jt::Vector2 const&) = default;
    Vector2& operator=(jt::Vector2&&) = default;

    operator sf::Vector2f() const { return m_vec; }

    float x() const override { return m_vec.x; };
    float y() const override { return m_vec.y; };

    float& x() override { return m_vec.x; }
    float& y() override { return m_vec.y; }

    jt::Vector2& operator+=(jt::Vector2 const& other)
    {
        m_vec.x += other.m_vec.x;
        m_vec.y += other.m_vec.y;
        return *this;
    }
    jt::Vector2& operator-=(jt::Vector2 const& other)
    {
        m_vec.x -= other.m_vec.x;
        m_vec.y -= other.m_vec.y;
        return *this;
    }

private:
    sf::Vector2f m_vec;
};

class Vector2u final : public Vector2uBase {
public:
    Vector2u()
        : m_vec { 0, 0 }
    {
    }
    Vector2u(unsigned int x, unsigned int y)
        : m_vec { x, y }
    {
    }

    Vector2u(sf::Vector2u const& v)
        : m_vec { v }
    {
    }

    ~Vector2u() = default;
    Vector2u(jt::Vector2u const&) = default;
    Vector2u(jt::Vector2u&&) = default;

    jt::Vector2u& operator=(jt::Vector2u const&) = default;
    jt::Vector2u& operator=(jt::Vector2u&&) = default;

    operator sf::Vector2u() const { return m_vec; }

    unsigned int x() const override { return m_vec.x; };
    unsigned int y() const override { return m_vec.y; };

    unsigned int& x() override { return m_vec.x; }
    unsigned int& y() override { return m_vec.y; }

    jt::Vector2u& operator+=(jt::Vector2u const& other)
    {
        m_vec.x += other.m_vec.x;
        m_vec.y += other.m_vec.y;
        return *this;
    }
    jt::Vector2u& operator-=(jt::Vector2u const& other)
    {
        m_vec.x -= other.m_vec.x;
        m_vec.y -= other.m_vec.y;
        return *this;
    }

private:
    sf::Vector2u m_vec;
};

} // namespace jt

#endif
