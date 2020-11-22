#include "SpriteFunctions.hpp"
#include "MathHelper.hpp"
#include <cmath>

namespace JamTemplate {

namespace SpriteFunctions {

sf::Image makeButtonImage(
    unsigned int w, unsigned int h, sf::Color midColor, sf::Color darkColor, sf::Color brightColor)
{
    sf::Image img {};
    img.create(3 * w, h, midColor);

    for (unsigned int i = 0; i != w; ++i) {
        img.setPixel(i, 0, brightColor);
        img.setPixel(i, h - 1, darkColor);

        img.setPixel(2 * w + i, 0, darkColor);
        img.setPixel(2 * w + i, h - 1, brightColor);
    }

    for (unsigned int j = 0; j != h; ++j) {
        img.setPixel(0, j, brightColor);
        img.setPixel(w - 1, j, darkColor);

        img.setPixel(2 * w, j, darkColor);
        img.setPixel(3 * w - 1, j, brightColor);
    }

    return img;
}

sf::Image makeGlowImage(float r, std::uint8_t max)
{
    unsigned int s = static_cast<unsigned int>(r + 0.5f * 2);
    sf::Image img {};
    img.create(s, s, sf::Color::Transparent);

    float const c = r / 2;

    for (auto i = 0U; i != s; ++i) {
        for (auto j = 0U; j != s; ++j) {
            auto const dx = i - c;
            auto const dy = j - c;

            auto const sqr = std::sqrt(dx * dx + dy * dy);
            auto const sqrNorm = 1.0f - MathHelper::clamp(sqr / s * 2.0f, 0.0f, 1.0f);
            float const v = std::pow(sqrNorm, 2.0f) * max;
            img.setPixel(i, j, sf::Color { 255, 255, 255, static_cast<uint8_t>(v) });
        }
    }
    return img;
}

sf::Image makeVignetteImage(unsigned int w, unsigned int h)
{
    sf::Image img {};
    float const cx = w / 2.0f;
    float const cy = h / 2.0f;
    img.create(w, h, sf::Color::Transparent);
    for (auto i = 0U; i != w; ++i) {
        for (auto j = 0U; j != h; ++j) {
            auto const dx = i - cx;
            auto const dy = j - cy;
            auto const sqr = std::sqrt(dx * dx + dy * dy);
            auto const sqrNorm = MathHelper::clamp(sqr / (cx + cy) / 1.5f * 2.0f, 0.0f, 1.0f);
            float const v = std::pow(sqrNorm, 2.0f) * 255;
            img.setPixel(i, j, sf::Color { 0, 0, 0, static_cast<uint8_t>(v) });
        }
    }
    return img;
}

} // namespace SpriteFunctions
} // namespace JamTemplate
