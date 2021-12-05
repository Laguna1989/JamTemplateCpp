#ifndef GUARD_JAMTEMAPLTE_SDL_SETUP_HPP
#define GUARD_JAMTEMAPLTE_SDL_SETUP_HPP

#include <memory>
#include "render_target.hpp"

#if !USE_SFML
#include <SDL2/SDL.h>

struct SDLSetup {
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderTarget;
    SDLSetup();
};

#endif

std::shared_ptr<jt::renderTarget> getRenderTarget();

#endif // GUARD_JAMTEMAPLTE_SDL_SETUP_HPP
