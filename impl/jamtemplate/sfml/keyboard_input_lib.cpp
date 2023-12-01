#include "keyboard_input_lib.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace {

sf::Keyboard::Key toLib(jt::KeyCode key) noexcept
{
    return static_cast<sf::Keyboard::Key>(key._value);
}

} // namespace

bool jt::libKeyValue(jt::KeyCode k)
{
    auto const libkey = toLib(k);
    return sf::Keyboard::isKeyPressed(libkey);
}
