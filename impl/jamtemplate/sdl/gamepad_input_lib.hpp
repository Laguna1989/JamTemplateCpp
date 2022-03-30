#ifndef GUARD_JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP
#define GUARD_JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP

#include "input/keyboard/keyboard_defaults.hpp"
#include "vector.hpp"

namespace jt {

jt::Vector2f libAxisValue(int gamepadId, jt::GamepadAxisCode a);

bool libGPButtonValue(int gamepadId, jt::GamepadButtonCode b);

} // namespace jt

#endif // GUARD_JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP
