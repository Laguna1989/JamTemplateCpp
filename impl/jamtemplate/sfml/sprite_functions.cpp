#include "sprite_functions.hpp"
#include "color_lib.hpp"
#include "math_helper.hpp"
#include "random/random.hpp"
#include <cmath>

namespace jt {

namespace SpriteFunctions {

sf::Image makeButtonImage(unsigned int w, unsigned int h)
{
    jt::Color emptyColor { 0, 0, 0 };
    jt::Color borderColor { 255, 255, 255 };
    jt::Color overBGColor { 150, 150, 150 };

    sf::Image img {};
    img.create(3 * w, h, toLib(emptyColor));

    for (unsigned int i = w; i != 3 * w; ++i) {
        for (unsigned int j = 0U; j != h; ++j) {
            img.setPixel(i, j, toLib(overBGColor));
        }
    }

    for (unsigned int i = 0U; i != w; ++i) {
        img.setPixel(i, 0U, toLib(borderColor));
        img.setPixel(i, h - 1, toLib(borderColor));

        img.setPixel(2 * w + i, 0, toLib(borderColor));
        img.setPixel(2 * w + i, h - 1, toLib(borderColor));
    }

    for (unsigned int j = 0U; j != h; ++j) {
        img.setPixel(0U, j, toLib(borderColor));
        img.setPixel(w - 1, j, toLib(borderColor));

        img.setPixel(2 * w, j, toLib(borderColor));
        img.setPixel(3 * w - 1, j, toLib(borderColor));
    }

    return img;
}

sf::Image makeBlankImage(unsigned int w, unsigned int h)
{
    sf::Image img {};
    img.create(w, h, sf::Color::White);
    return img;
}

sf::Image makeGlowImage(float r, std::uint8_t max)
{
    auto const s = static_cast<unsigned int>(r + 0.5f * 2);
    sf::Image img {};
    img.create(s, s, toLib(jt::colors::Transparent));

    float const c = r / 2;

    for (auto i = 0U; i != s; ++i) {
        for (auto j = 0U; j != s; ++j) {
            auto const dx = i - c;
            auto const dy = j - c;

            auto const sqr = std::sqrt(dx * dx + dy * dy);
            auto const sqrNorm
                = 1.0f - MathHelper::clamp(sqr / static_cast<float>(s) * 2.0f, 0.0f, 1.0f);
            float const v = std::pow(sqrNorm, 2.0f) * static_cast<float>(max);
            img.setPixel(i, j, toLib(jt::Color { 255, 255, 255, static_cast<uint8_t>(v) }));
        }
    }
    return img;
}

sf::Image makeVignetteImage(unsigned int w, unsigned int h)
{
    sf::Image img {};
    auto const cx = static_cast<float>(w) / 2.0f;
    auto const cy = static_cast<float>(h) / 2.0f;
    img.create(w, h, toLib(jt::colors::Transparent));
    for (auto i = 0U; i != w; ++i) {
        for (auto j = 0U; j != h; ++j) {
            auto const dx = static_cast<float>(i) - cx;
            auto const dy = static_cast<float>(j) - cy;
            auto const sqr = std::sqrt(dx * dx + dy * dy);
            auto const sqrNorm = MathHelper::clamp(sqr / (cx + cy) / 1.5f * 2.0f, 0.0f, 1.0f);
            float const v = std::pow(sqrNorm, 2.0f) * 235 + jt::Random::getInt(0, 20);
            img.setPixel(i, j, toLib(jt::Color { 0, 0, 0, static_cast<uint8_t>(v) }));
        }
    }
    return img;
}

} // namespace SpriteFunctions
} // namespace jt
