#include "mouse_input_lib.hpp"
#include <SFML/Window/Mouse.hpp>

namespace jt {

// it is not possible to get mouse input for automated unittests
// GCOV_EXCL_START
namespace {
sf::Mouse::Button toLib(jt::MouseButtonCode key) { return static_cast<sf::Mouse::Button>(key); }
} // namespace

bool libKeyValue(jt::MouseButtonCode b)
{
    auto const libkey = toLib(b);
    return sf::Mouse::isButtonPressed(libkey);
}
// GCOV_EXCL_STOP
} // namespace jt
