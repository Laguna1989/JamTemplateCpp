#include "mouse_input_lib.hpp"
#include <SDL2/SDL.h>
#include <cstdint>

namespace jt {

namespace {
std::uint8_t toLib(jt::MouseButtonCode key)
{
    switch (key) {
    case MouseButtonCode::MBLeft:
        return SDL_BUTTON_LEFT;
    case MouseButtonCode::MBMiddle:
        return SDL_BUTTON_MIDDLE;
    case MouseButtonCode::MBRight:
        return SDL_BUTTON_RIGHT;

    default:
        return SDL_BUTTON_MIDDLE;
    }
}

} // namespace

bool libKeyValue(jt::MouseButtonCode b)
{
    SDL_PumpEvents();
    int x { 0 };
    int y { 0 };
    auto const mouseState = SDL_GetMouseState(&x, &y);

    return ((mouseState & SDL_BUTTON(toLib(b))) != 0u);
}

} // namespace jt
