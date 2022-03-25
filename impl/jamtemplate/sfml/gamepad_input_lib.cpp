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

} // namespace

jt::Vector2f jt::libAxisValue(jt::GamepadAxisCode a)
{
    if (!sf::Joystick::isConnected(0)) {
        return jt::Vector2f { 0.0f, 0.0f };
    }

    auto const libaxis = toLib(a);

    float x { 0.0f };
    if (sf::Joystick::hasAxis(0, libaxis.first)) {
        x = sf::Joystick::getAxisPosition(0, libaxis.first);
    }
    float y { 0.0f };
    if (sf::Joystick::hasAxis(0, libaxis.second)) {
        y = sf::Joystick::getAxisPosition(0, libaxis.second);
    }
    return jt::Vector2f { x, y };
}
