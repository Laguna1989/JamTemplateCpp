#ifndef GUARD_JAMTEMPLATE_GAMEPAD_DEFINES_HPP
#define GUARD_JAMTEMPLATE_GAMEPAD_DEFINES_HPP

#include <vector>

namespace jt {

// TODO more axis
enum class GamepadAxisCode {
    ALeft,
    ARight,
    AxisCount ///< Keep last -- the total number of gamepad axis
};

enum class GamepadButtonCode {
    GBA,
    GBB,
    GBX,
    GBY,
    GBLB,
    GBRB,
    GBBack,
    GBStart,
    GBLeftStick,
    GBRightStick,
    GBU1,
    GBU2,
    GBU3,
    GBU4,
    GBU5,
    GBU6,
    GBU7,
    GBU8,
    GPButtonCount ///< Keep last -- the total number of gamepad button
};

std::vector<jt::GamepadAxisCode> getAllAxis();
std::vector<jt::GamepadButtonCode> getAllGamepadButtons();

} // namespace jt

#endif // GUARD_JAMTEMPLATE_GAMEPAD_DEFINES_HPP
