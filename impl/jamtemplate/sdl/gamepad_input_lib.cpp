#include "gamepad_input_lib.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <memory>

namespace {
std::pair<SDL_GameControllerAxis, SDL_GameControllerAxis> toLib(jt::GamepadAxisCode axis)
{
    if (axis == jt::GamepadAxisCode::ALeft) {
        return std::make_pair(SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY);
    } else if (axis == jt::GamepadAxisCode::ARight) {
        return std::make_pair(SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY);
    }
    return std::make_pair(SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY);
}

int toLib(jt::GamepadButtonCode b) { return static_cast<int>(b); }

std::shared_ptr<SDL_GameController> createGamepad(int gamepadId)
{
    std::shared_ptr<SDL_GameController> controller = nullptr;

    if (SDL_IsGameController(gamepadId)) {
        controller = std::shared_ptr<SDL_GameController>(
            SDL_GameControllerOpen(gamepadId), SDL_GameControllerClose);
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
    //    std::cout << SDL_NumJoysticks() << std::endl;
    auto currentGamepad = getGamepad(gamepadId).get();

    if (!SDL_GameControllerGetAttached(currentGamepad)) {
        return jt::Vector2f { 0.0f, 0.0f };
    }

    auto const libaxis = toLib(a);

    float x = SDL_GameControllerGetAxis(currentGamepad, libaxis.first) / 32767.0f * 100.0f;
    float y = SDL_GameControllerGetAxis(currentGamepad, libaxis.second) / 32767.0f * 100.0f;
    return jt::Vector2f { x, y };
}

bool jt::libGPButtonValue(int gamepadId, jt::GamepadButtonCode b) { return false; }
