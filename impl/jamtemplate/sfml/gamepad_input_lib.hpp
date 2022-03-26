#ifndef GUARD_JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP
#define GUARD_JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP

#include "input/key_codes.hpp"
#include "vector.hpp"

namespace jt {

Vector2f libAxisValue(jt::GamepadAxisCode a);

bool libGPButtonValue(jt::GamepadButtonCode b);

} // namespace jt

#endif // GUARD_JAMTEMPLATE_GAMEPAD_INPUT_LIB_HPP
