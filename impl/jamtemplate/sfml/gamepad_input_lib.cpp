#include "gamepad_input_lib.hpp"
#include <SFML/Window/Joystick.hpp>

namespace {
std::pair<sf::Joystick::Axis, sf::Joystick::Axis> toLib(jt::GamepadAxisCode axis)
{
    if (axis._value == jt::GamepadAxisCode::ALeft) {
        return std::make_pair(sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
    } else if (axis._value == jt::GamepadAxisCode::ARight) {
        return std::make_pair(sf::Joystick::Axis::U, sf::Joystick::Axis::V);
    }
    return std::make_pair(sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
}

int toLib(jt::GamepadButtonCode b) { return static_cast<int>(b); }

} // namespace

jt::Vector2f jt::libAxisValue(int gamepadId, jt::GamepadAxisCode a)
{
    auto const libaxis = toLib(a);

    if (!sf::Joystick::isConnected(gamepadId)) {
        return jt::Vector2f { 0.0f, 0.0f };
    }

    float x { 0.0f };
    if (sf::Joystick::hasAxis(gamepadId, libaxis.first)) {
        x = sf::Joystick::getAxisPosition(gamepadId, libaxis.first);
    }
    float y { 0.0f };
    if (sf::Joystick::hasAxis(gamepadId, libaxis.second)) {
        y = sf::Joystick::getAxisPosition(gamepadId, libaxis.second);
    }
    return jt::Vector2f { x, y };
}

bool jt::libGPButtonValue(int gamepadId, jt::GamepadButtonCode b)
{
    auto const libButton = toLib(b);
    return sf::Joystick::isButtonPressed(gamepadId, libButton);
}
