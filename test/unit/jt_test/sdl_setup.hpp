#ifndef GUARD_JAMTEMAPLTE_SDL_SETUP_HPP
#define GUARD_JAMTEMAPLTE_SDL_SETUP_HPP

#if !USE_SFML
#include <SDL2/SDL.h>
#include <memory>

struct SDLSetup {
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderTarget;
    SDLSetup();
};

#endif

#endif // GUARD_JAMTEMAPLTE_SDL_SETUP_HPP
