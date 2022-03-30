#include "gamepad_defines.hpp"
#include <cstdint>

std::vector<jt::GamepadAxisCode> jt::getAllAxis()
{
    auto const maxValue = static_cast<std::uint32_t>(jt::GamepadAxisCode::AxisCount);
    std::vector<jt::GamepadAxisCode> values(maxValue, jt::GamepadAxisCode::ALeft);
    for (std::uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::GamepadAxisCode>(i);
    }
    return values;
}
std::vector<jt::GamepadButtonCode> jt::getAllGamepadButtons()
{
    auto const maxValue = static_cast<std::uint32_t>(jt::GamepadButtonCode::GPButtonCount);
    std::vector<jt::GamepadButtonCode> values(maxValue, jt::GamepadButtonCode::GBA);
    for (std::uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::GamepadButtonCode>(i);
    }
    return values;
}
