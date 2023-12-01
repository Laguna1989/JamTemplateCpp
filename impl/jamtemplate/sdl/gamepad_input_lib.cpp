#include "gamepad_input_lib.hpp"
#include <sdl_2_include.hpp>
#include <iostream>
#include <map>
#include <memory>

namespace {
std::pair<SDL_GameControllerAxis, SDL_GameControllerAxis> toLib(jt::GamepadAxisCode axis)
{
    if (axis._value == jt::GamepadAxisCode::ALeft) {
        return std::make_pair(SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY);
    } else if (axis._value == jt::GamepadAxisCode::ARight) {
        return std::make_pair(SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY);
    }
    return std::make_pair(SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY);
}

SDL_GameControllerButton toLib(jt::GamepadButtonCode b) noexcept
{
    switch (b) {
    case jt::GamepadButtonCode::GBA:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBA);
    case jt::GamepadButtonCode::GBB:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBB);
    case jt::GamepadButtonCode::GBX:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBX);
    case jt::GamepadButtonCode::GBY:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBY);
    case jt::GamepadButtonCode::GBLB:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBRightStick);
    case jt::GamepadButtonCode::GBRB:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU1);
    case jt::GamepadButtonCode::GBBack:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBLB);
    case jt::GamepadButtonCode::GBStart:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBBack);
    case jt::GamepadButtonCode::GBLeftStick:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBStart);
    case jt::GamepadButtonCode::GBRightStick:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBLeftStick);
    case jt::GamepadButtonCode::GBU1:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU8);
    case jt::GamepadButtonCode::GBU2:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU2);
    case jt::GamepadButtonCode::GBU3:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU3);
    case jt::GamepadButtonCode::GBU4:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU4);
    case jt::GamepadButtonCode::GBU5:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU5);
    case jt::GamepadButtonCode::GBU6:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU6);
    case jt::GamepadButtonCode::GBU7:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU7);
    case jt::GamepadButtonCode::GBU8:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU8);
    default:
        return static_cast<SDL_GameControllerButton>(jt::GamepadButtonCode::GBU8);
    }
}

std::shared_ptr<SDL_GameController> createGamepad(int gamepadId)
{
    std::shared_ptr<SDL_GameController> controller = nullptr;

    if (SDL_IsGameController(gamepadId)) {
        controller = std::shared_ptr<SDL_GameController>(
            SDL_GameControllerOpen(gamepadId), SDL_GameControllerClose);
        std::cout << "create new controller: " << controller.get() << std::endl;
    }
    return controller;
}

std::shared_ptr<SDL_GameController> getGamepad(int gamepadId)
{
    static std::map<int, std::shared_ptr<SDL_GameController>> gamepads;

    if (!gamepads.contains(gamepadId) || gamepads.at(gamepadId) == nullptr) {
        gamepads[gamepadId] = createGamepad(gamepadId);
    }
    return gamepads[gamepadId];
}

} // namespace

jt::Vector2f jt::libAxisValue(int gamepadId, jt::GamepadAxisCode a)
{
    auto const currentGamepad = getGamepad(gamepadId).get();

    if (!SDL_GameControllerGetAttached(currentGamepad)) {
        return jt::Vector2f { 0.0f, 0.0f };
    }

    auto const [xAxis, yAxis] = toLib(a);

    return jt::Vector2f { (SDL_GameControllerGetAxis(currentGamepad, xAxis) / 32767.0f * 100.0f),
        (SDL_GameControllerGetAxis(currentGamepad, yAxis) / 32767.0f * 100.0f) };
}

bool jt::libGPButtonValue(int gamepadId, jt::GamepadButtonCode b)
{
    auto const currentGamepad = getGamepad(gamepadId).get();

    if (!SDL_GameControllerGetAttached(currentGamepad)) {
        return false;
    }

    auto const libButton = toLib(b);
    return static_cast<bool>(SDL_GameControllerGetButton(currentGamepad, libButton));
}
