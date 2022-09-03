#ifndef JAMTEMPLATE_SPRITEFUNCTIONS_HPP
#define JAMTEMPLATE_SPRITEFUNCTIONS_HPP

#include <color/color.hpp>
#include <SFML/Graphics.hpp>

namespace jt {
namespace SpriteFunctions {

sf::Image makeButtonImage(unsigned int w, unsigned int h);

sf::Image makeGlowImage(float r, std::uint8_t max = 255);

sf::Image makeVignetteImage(unsigned int w, unsigned int h);

sf::Image makeBlankImage(unsigned int w, unsigned int h);

sf::Image makeRing(unsigned int w);

} // namespace SpriteFunctions

} // namespace jt

#endif
