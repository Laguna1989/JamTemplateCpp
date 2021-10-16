#ifndef GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP

#include "vector_base.hpp"
#include <SDL2/SDL.h>

namespace jt {

class Vector2 final : public Vector2Base {
public:
    Vector2()
        : m_x { 0 }
        , m_y { 0 }
    {
    }
    Vector2(float x, float y)
        : m_x { x }
        , m_y { y }
    {
    }

    Vector2(SDL_Point const& v)
        : m_x { static_cast<float>(v.x) }
        , m_y { static_cast<float>(v.y) }
    {
    }

    ~Vector2() = default;
    Vector2(jt::Vector2 const&) = default;
    Vector2(jt::Vector2&&) = default;

    Vector2& operator=(jt::Vector2 const&) = default;
    Vector2& operator=(jt::Vector2&&) = default;

    operator SDL_Point() const
    {
        return SDL_Point { static_cast<int>(m_x), static_cast<int>(m_y) };
    }

    float x() const override { return m_x; };
    float y() const override { return m_y; };

    float& y() override { return m_y; }
    float& x() override { return m_x; }

    jt::Vector2& operator+=(jt::Vector2 const& other)
    {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }
    jt::Vector2& operator-=(jt::Vector2 const& other)
    {
        m_x -= other.m_x;
        m_y -= other.m_y;
        return *this;
    }

private:
    float m_x;
    float m_y;
};

class Vector2u final : public Vector2uBase {
public:
    Vector2u()
        : m_x { 0U }
        , m_y { 0U }
    {
    }
    Vector2u(unsigned int x, unsigned int y)
        : m_x { x }
        , m_y { y }
    {
    }

    Vector2u(SDL_Point const& v)
        : m_x { static_cast<unsigned int>(v.x) }
        , m_y { static_cast<unsigned int>(v.y) }
    {
    }

    ~Vector2u() = default;
    Vector2u(jt::Vector2u const&) = default;
    Vector2u(jt::Vector2u&&) = default;

    jt::Vector2u& operator=(jt::Vector2u const&) = default;
    jt::Vector2u& operator=(jt::Vector2u&&) = default;

    operator SDL_Point() const
    {
        return SDL_Point { static_cast<int>(m_x), static_cast<int>(m_y) };
    }

    unsigned int x() const override { return m_x; };
    unsigned int y() const override { return m_y; };

    unsigned int& x() override { return m_x; }
    unsigned int& y() override { return m_y; }

    jt::Vector2u& operator+=(jt::Vector2u const& other)
    {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }
    jt::Vector2u& operator-=(jt::Vector2u const& other)
    {
        m_x -= other.m_x;
        m_y -= other.m_y;
        return *this;
    }

private:
    unsigned int m_x;
    unsigned int m_y;
};

} // namespace jt

#endif
