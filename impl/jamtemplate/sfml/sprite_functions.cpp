#include "sprite_functions.hpp"
#include <color_lib.hpp>
#include <math_helper.hpp>
#include <random/random.hpp>
#include <algorithm>
#include <cmath>
#include <numbers>

sf::Image jt::SpriteFunctions::makeButtonImage(unsigned int w, unsigned int h)
{
    constexpr jt::Color emptyColor { 0, 0, 0 };
    constexpr jt::Color borderColor { 255, 255, 255 };
    constexpr jt::Color overBGColor { 150, 150, 150 };

    sf::Image img {};
    img.create(3 * w, h, toLib(emptyColor));

    for (unsigned int i = w; i != 3 * w; ++i) {
        for (unsigned int j = 0u; j != h; ++j) {
            img.setPixel(i, j, toLib(overBGColor));
        }
    }

    for (unsigned int i = 0u; i != w; ++i) {
        img.setPixel(i, 0u, toLib(borderColor));
        img.setPixel(i, h - 1, toLib(borderColor));

        img.setPixel(2 * w + i, 0, toLib(borderColor));
        img.setPixel(2 * w + i, h - 1, toLib(borderColor));
    }

    for (unsigned int j = 0u; j != h; ++j) {
        img.setPixel(0u, j, toLib(borderColor));
        img.setPixel(w - 1, j, toLib(borderColor));

        img.setPixel(2 * w, j, toLib(borderColor));
        img.setPixel(3 * w - 1, j, toLib(borderColor));
    }

    return img;
}

sf::Image jt::SpriteFunctions::makeBlankImage(unsigned int w, unsigned int h)
{
    sf::Image img {};
    img.create(w, h, sf::Color::White);
    return img;
}

sf::Image jt::SpriteFunctions::makeGlowImage(float r, std::uint8_t max)
{
    auto const s = static_cast<unsigned int>(r + 0.5f * 2);
    sf::Image img {};
    img.create(s, s, toLib(jt::colors::Transparent));

    float const c = r / 2;

    for (auto i = 0u; i != s; ++i) {
        for (auto j = 0u; j != s; ++j) {
            auto const dx = i - c;
            auto const dy = j - c;

            auto const sqr = jt::MathHelper::qsqrt(dx * dx + dy * dy);
            auto const sqrNorm = 1.0f - std::clamp(sqr / static_cast<float>(s) * 2.0f, 0.0f, 1.0f);
            float const v = std::pow(sqrNorm, 2.0f) * static_cast<float>(max);
            img.setPixel(i, j, toLib(jt::Color { 255, 255, 255, static_cast<uint8_t>(v) }));
        }
    }
    return img;
}

sf::Image jt::SpriteFunctions::makeVignetteImage(unsigned int w, unsigned int h)
{
    sf::Image img {};
    auto const cx = static_cast<float>(w) / 2.0f;
    auto const cy = static_cast<float>(h) / 2.0f;
    img.create(w, h, toLib(jt::colors::Transparent));
    for (auto i = 0u; i != w; ++i) {
        for (auto j = 0u; j != h; ++j) {
            auto const dx = static_cast<float>(i) - cx;
            auto const dy = static_cast<float>(j) - cy;
            auto const sqr = jt::MathHelper::qsqrt(dx * dx + dy * dy);
            auto const sqrNorm = std::clamp(sqr / (cx + cy) / 1.5f * 2.0f, 0.0f, 1.0f);
            float const v = std::pow(sqrNorm, 3.5f) * 245 + jt::Random::getInt(0, 10);
            img.setPixel(i, j, toLib(jt::Color { 0, 0, 0, static_cast<uint8_t>(v) }));
        }
    }
    return img;
}

sf::Image jt::SpriteFunctions::makeRing(unsigned int w)
{
    sf::Image img {};
    float const r = w / 2.0f;
    float const minAngle = acos(1 - 1 / r);
    img.create(w + 1, w + 1, toLib(jt::colors::Transparent));

    for (auto a = 0.0f; a <= 90.0f; a += minAngle) {
        float const xo = sin(a * std::numbers::pi / 180.0f) * r;
        float const yo = cos(a * std::numbers::pi / 180.0f) * r;
        img.setPixel(static_cast<unsigned int>(r + xo), static_cast<unsigned int>(r + yo),
            toLib(jt::Color { 255, 255, 255, 255 }));
        img.setPixel(static_cast<unsigned int>(r + xo), static_cast<unsigned int>(r - yo),
            toLib(jt::Color { 255, 255, 255, 255 }));
        img.setPixel(static_cast<unsigned int>(r - xo), static_cast<unsigned int>(r + yo),
            toLib(jt::Color { 255, 255, 255, 255 }));
        img.setPixel(static_cast<unsigned int>(r - xo), static_cast<unsigned int>(r - yo),
            toLib(jt::Color { 255, 255, 255, 255 }));
    }
    return img;
}
