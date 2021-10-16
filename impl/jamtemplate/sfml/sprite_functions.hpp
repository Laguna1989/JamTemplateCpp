#ifndef GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD

#include "color.hpp"
#include <SFML/Graphics.hpp>

namespace jt {
namespace SpriteFunctions {

sf::Image makeButtonImage(unsigned int w, unsigned int h);

sf::Image makeGlowImage(float r, std::uint8_t max = 255);

sf::Image makeVignetteImage(unsigned int w, unsigned int h);

sf::Image makeBlankImage(unsigned int w, unsigned int h);

} // namespace SpriteFunctions

} // namespace jt

#endif
