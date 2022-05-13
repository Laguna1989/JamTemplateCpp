#include "keyboard_input_lib.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace {
sf::Keyboard::Key toLib(jt::KeyCode key) { return static_cast<sf::Keyboard::Key>(key._value); }
} // namespace

bool jt::libKeyValue(jt::KeyCode b)
{
    auto const libkey = toLib(b);
    return sf::Keyboard::isKeyPressed(libkey);
}
