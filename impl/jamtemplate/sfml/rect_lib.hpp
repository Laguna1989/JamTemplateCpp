#ifndef JAMTEMPLATE_RECT_LIB_HPP
#define JAMTEMPLATE_RECT_LIB_HPP

#include <SFML/Graphics/Rect.hpp>
#include <rect.hpp>

namespace jt {

sf::FloatRect toLib(jt::Rectf const& rect) noexcept;
jt::Rectf fromLib(sf::Rect<float> rect) noexcept;

sf::IntRect toLib(jt::Recti const& rect) noexcept;
jt::Recti fromLib(sf::IntRect const& rect) noexcept;

} // namespace jt

#endif
