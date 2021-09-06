#include "keyboard_input_lib.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace jt {

// it is not possible to get keyboard input for automated unittests
// GCOV_EXCL_START
namespace {
sf::Keyboard::Key toLib(jt::KeyCode key) { return static_cast<sf::Keyboard::Key>(key); }
} // namespace

bool libKeyValue(jt::KeyCode b)
{
    auto const libkey = toLib(b);
    return sf::Keyboard::isKeyPressed(libkey);
}

// GCOV_EXCL_STOP
} // namespace jt
