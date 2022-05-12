#include "gamepad_defines.hpp"
#include <cstdint>

std::vector<jt::GamepadAxisCode> jt::getAllAxis()
{
    std::vector<GamepadAxisCode> values(GamepadAxisCode::_size(), GamepadAxisCode::ALeft);
    for (auto k : GamepadAxisCode::_values()) {
        values.at(k) = k;
    }
    return values;
}
std::vector<jt::GamepadButtonCode> jt::getAllGamepadButtons()
{
    std::vector<GamepadButtonCode> values(GamepadButtonCode::_size(), jt::GamepadButtonCode::GBA);
    for (auto k : GamepadButtonCode::_values()) {
        values.at(k) = k;
    }
    return values;
}
