#include "gamepad_input_lib.hpp"
#include <SDL2/SDL.h>
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

SDL_GameControllerButton toLib(jt::GamepadButtonCode b)
{
    std::map<jt::GamepadButtonCode, jt::GamepadButtonCode> lookup {
        { jt::GamepadButtonCode::GBA, jt::GamepadButtonCode::GBA },
        { jt::GamepadButtonCode::GBB, jt::GamepadButtonCode::GBB },
        { jt::GamepadButtonCode::GBX, jt::GamepadButtonCode::GBX },
        { jt::GamepadButtonCode::GBY, jt::GamepadButtonCode::GBY },
        { jt::GamepadButtonCode::GBLB, jt::GamepadButtonCode::GBRightStick },
        { jt::GamepadButtonCode::GBRB, jt::GamepadButtonCode::GBU1 },
        { jt::GamepadButtonCode::GBBack, jt::GamepadButtonCode::GBLB },
        { jt::GamepadButtonCode::GBStart, jt::GamepadButtonCode::GBBack },
        { jt::GamepadButtonCode::GBLeftStick, jt::GamepadButtonCode::GBStart },
        { jt::GamepadButtonCode::GBRightStick, jt::GamepadButtonCode::GBLeftStick },
        { jt::GamepadButtonCode::GBU1, jt::GamepadButtonCode::GBU8 },
        { jt::GamepadButtonCode::GBU2, jt::GamepadButtonCode::GBU2 },
        { jt::GamepadButtonCode::GBU3, jt::GamepadButtonCode::GBU3 },
        { jt::GamepadButtonCode::GBU4, jt::GamepadButtonCode::GBU4 },
        { jt::GamepadButtonCode::GBU5, jt::GamepadButtonCode::GBU5 },
        { jt::GamepadButtonCode::GBU6, jt::GamepadButtonCode::GBU6 },
        { jt::GamepadButtonCode::GBU7, jt::GamepadButtonCode::GBU7 },
        { jt::GamepadButtonCode::GBU8, jt::GamepadButtonCode::GBU8 }
    };

    return static_cast<SDL_GameControllerButton>(lookup[b]._value);
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

    if (gamepads.count(gamepadId) == 0 || gamepads.at(gamepadId) == nullptr) {
        gamepads[gamepadId] = createGamepad(gamepadId);
    }
    return gamepads[gamepadId];
}

} // namespace

jt::Vector2f jt::libAxisValue(int gamepadId, jt::GamepadAxisCode a)
{
    auto currentGamepad = getGamepad(gamepadId).get();

    if (!SDL_GameControllerGetAttached(currentGamepad)) {
        return jt::Vector2f { 0.0f, 0.0f };
    }

    auto const libaxis = toLib(a);

    float x = SDL_GameControllerGetAxis(currentGamepad, libaxis.first) / 32767.0f * 100.0f;
    float y = SDL_GameControllerGetAxis(currentGamepad, libaxis.second) / 32767.0f * 100.0f;
    return jt::Vector2f { x, y };
}

bool jt::libGPButtonValue(int gamepadId, jt::GamepadButtonCode b)
{
    auto currentGamepad = getGamepad(gamepadId).get();

    if (!SDL_GameControllerGetAttached(currentGamepad)) {
        return false;
    }

    auto const libButton = toLib(b);
    return static_cast<bool>(SDL_GameControllerGetButton(currentGamepad, libButton));
}
