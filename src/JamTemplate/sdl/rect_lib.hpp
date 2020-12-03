﻿#ifndef GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_RECT_LIB_GUARD_HPP

#include "rect_base.hpp"
#include <SDL.h>

namespace jt {

class rect final : public rectBase {
public:
    rect()
        : m_left { 0.0f }
        , m_top { 0.0f }
        , m_width { 0.0f }
        , m_height { 0.0f }
    {
    }

    rect(float left, float top, float width, float height)
        : m_left { left }
        , m_top { top }
        , m_width { width }
        , m_height { height }
    {
    }

    rect(SDL_Rect const& v)
        : m_left { static_cast<float>(v.x) }
        , m_top { static_cast<float>(v.y) }
        , m_width { static_cast<float>(v.w) }
        , m_height { static_cast<float>(v.h) }
    {
    }

    ~rect() = default;
    rect(jt::rect const&) = default;
    rect(jt::rect&&) = default;

    rect& operator=(jt::rect const&) = default;
    rect& operator=(jt::rect&&) = default;

    operator SDL_Rect() const
    {
        return SDL_Rect { static_cast<int>(m_left), static_cast<int>(m_top),
            static_cast<int>(m_width), static_cast<int>(m_height) };
    }

    float left() const override { return m_left; };
    float top() const override { return m_top; };
    float width() const override { return m_width; };
    float height() const override { return m_height; };
    float& left() override { return m_left; };
    float& top() override { return m_top; };
    float& width() override { return m_width; };
    float& height() override { return m_height; };

private:
    float m_left;
    float m_top;
    float m_width;
    float m_height;
}; // namespace jt

class recti final : public rectiBase {
public:
    recti()
        : recti { 0, 0, 0, 0 }
    {
    }
    recti(int left, int top, int width, int height)
        : m_rect { left, top, width, height }
    {
    }

    recti(SDL_Rect const& v)
        : m_rect { v }
    {
    }

    ~recti() = default;
    recti(jt::recti const&) = default;
    recti(jt::recti&&) = default;

    recti& operator=(jt::recti const&) = default;
    recti& operator=(jt::recti&&) = default;

    operator SDL_Rect() const { return m_rect; }

    SDL_Rect m_rect;

    int left() const override { return m_rect.x; };
    int top() const override { return m_rect.y; };
    int width() const override { return m_rect.w; };
    int height() const override { return m_rect.h; };
    int& left() override { return m_rect.x; };
    int& top() override { return m_rect.y; };
    int& width() override { return m_rect.w; };
    int& height() override { return m_rect.h; };
};

} // namespace jt

#endif
