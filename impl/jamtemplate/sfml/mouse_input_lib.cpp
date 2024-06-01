#include "mouse_input_lib.hpp"
#include <SFML/Window/Mouse.hpp>

namespace {

sf::Mouse::Button toLib(jt::MouseButtonCode key) noexcept
{
    return static_cast<sf::Mouse::Button>(key);
}

} // namespace

bool jt::libKeyValue(jt::MouseButtonCode b)
{
    auto const libKey = toLib(b);
    return sf::Mouse::isButtonPressed(libKey);
}
