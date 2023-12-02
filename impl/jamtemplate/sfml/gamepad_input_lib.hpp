#ifndef JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP
#define JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP

#include <input/gamepad/gamepad_defines.hpp>
#include <vector.hpp>

namespace jt {

jt::Vector2f libAxisValue(int gamepadId, jt::GamepadAxisCode a);

bool libGPButtonValue(int gamepadId, jt::GamepadButtonCode b);

} // namespace jt

#endif // JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP
