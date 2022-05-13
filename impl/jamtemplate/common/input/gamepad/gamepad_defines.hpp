#ifndef JAMTEMPLATE_GAMEPAD_DEFINES_HPP
#define JAMTEMPLATE_GAMEPAD_DEFINES_HPP

#include <enum.h>
#include <enum_macros.h>
#include <vector>

namespace jt {

// TODO more axis
BETTER_ENUM(GamepadAxisCode, int, ALeft = 0, ARight)

BETTER_ENUM(GamepadButtonCode, int, GBA = 0, GBB, GBX, GBY, GBLB, GBRB, GBBack, GBStart,
    GBLeftStick, GBRightStick, GBU1, GBU2, GBU3, GBU4, GBU5, GBU6, GBU7, GBU8)

std::vector<jt::GamepadAxisCode> getAllAxis();
std::vector<jt::GamepadButtonCode> getAllGamepadButtons();

} // namespace jt

#endif // JAMTEMPLATE_GAMEPAD_DEFINES_HPP
