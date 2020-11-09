#ifndef JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>

namespace JamTemplate {
namespace SpriteFunctions {

sf::Image makeButtonImage(unsigned int w, unsigned int h,
    sf::Color midColor = sf::Color { 200, 200, 200 },
    sf::Color darkColor = sf::Color { 100, 100, 100 },
    sf::Color brightColor = sf::Color { 255, 255, 255 });

sf::Image makeGlowImage(float r, std::uint8_t max = 255);

sf::Image makeVignetteImage(unsigned int w, unsigned int h);

} // namespace SpriteFunctions

} // namespace JamTemplate

#endif
