#ifndef GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_VECTOR_LIB_GUARD_HPP

#include "vector_base.hpp"
#include <SDL.h>

namespace jt {

class vector2 final : public vector2Base {
public:
    vector2()
        : m_x { 0 }
        , m_y { 0 }
    {
    }
    vector2(float x, float y)
        : m_x { x }
        , m_y { y }
    {
    }

    vector2(SDL_Point const& v)
        : m_x { static_cast<float>(v.x) }
        , m_y { static_cast<float>(v.y) }
    {
    }

    ~vector2() = default;
    vector2(jt::vector2 const&) = default;
    vector2(jt::vector2&&) = default;

    vector2& operator=(jt::vector2 const&) = default;
    vector2& operator=(jt::vector2&&) = default;

    operator SDL_Point() const
    {
        return SDL_Point { static_cast<int>(m_x), static_cast<int>(m_y) };
    }

    float x() const override { return m_x; };
    float y() const override { return m_y; };

    float& y() override { return m_y; }
    float& x() override { return m_x; }

private:
    float m_x;
    float m_y;
};

class vector2u final : public vector2uBase {
public:
    vector2u()
        : m_x { 0U }
        , m_y { 0U }
    {
    }
    vector2u(unsigned int x, unsigned int y)
        : m_x { x }
        , m_y { y }
    {
    }

    vector2u(SDL_Point const& v)
        : m_x { static_cast<unsigned int>(v.x) }
        , m_y { static_cast<unsigned int>(v.y) }
    {
    }

    ~vector2u() = default;
    vector2u(jt::vector2u const&) = default;
    vector2u(jt::vector2u&&) = default;

    jt::vector2u& operator=(jt::vector2u const&) = default;
    jt::vector2u& operator=(jt::vector2u&&) = default;

    operator SDL_Point() const
    {
        return SDL_Point { static_cast<int>(m_x), static_cast<int>(m_y) };
    }

    unsigned int x() const override { return m_x; };
    unsigned int y() const override { return m_y; };

    unsigned int& x() override { return m_x; }
    unsigned int& y() override { return m_y; }

private:
    unsigned int m_x;
    unsigned int m_y;
};

} // namespace jt

#endif
