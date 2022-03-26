#include "gamepad_input_lib.hpp"
#include <SFML/Window/Joystick.hpp>

namespace {
std::pair<sf::Joystick::Axis, sf::Joystick::Axis> toLib(jt::GamepadAxisCode axis)
{

    if (axis == jt::GamepadAxisCode::ALeft) {
        return std::make_pair(sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
    } else if (axis == jt::GamepadAxisCode::ARight) {
        return std::make_pair(sf::Joystick::Axis::U, sf::Joystick::Axis::V);
    }
    return std::make_pair(sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
}

int toLib(jt::GamepadButtonCode b) { return static_cast<int>(b); }

} // namespace

jt::Vector2f jt::libAxisValue(jt::GamepadAxisCode a)
{
    if (!sf::Joystick::isConnected(0)) {
        return jt::Vector2f { 0.0f, 0.0f };
    }

    auto const libaxis = toLib(a);

    float x { 0.0f };
    // TODO add support for multiple gampads
    if (sf::Joystick::hasAxis(0, libaxis.first)) {
        x = sf::Joystick::getAxisPosition(0, libaxis.first);
    }
    float y { 0.0f };
    if (sf::Joystick::hasAxis(0, libaxis.second)) {
        y = sf::Joystick::getAxisPosition(0, libaxis.second);
    }
    return jt::Vector2f { x, y };
}

bool jt::libGPButtonValue(jt::GamepadButtonCode b)
{
    auto const libButton = toLib(b);
    // TODO add support for multiple gampads
    return sf::Joystick::isButtonPressed(0, libButton);
}
