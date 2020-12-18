#ifndef GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD

#include "Color.hpp"
#include <SFML/Graphics.hpp>

namespace jt {
namespace SpriteFunctions {

sf::Image makeButtonImage(unsigned int w, unsigned int h,
    jt::Color midColor = jt::Color { 200, 200, 200 },
    jt::Color darkColor = jt::Color { 100, 100, 100 },
    jt::Color brightColor = jt::Color { 255, 255, 255 });

sf::Image makeGlowImage(float r, std::uint8_t max = 255);

sf::Image makeVignetteImage(unsigned int w, unsigned int h);

} // namespace SpriteFunctions

} // namespace jt

#endif
