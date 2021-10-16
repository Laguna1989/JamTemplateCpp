#ifndef MYAWESOMEGAME_SDL_SETUP_HPP
#define MYAWESOMEGAME_SDL_SETUP_HPP

#if !USE_SFML
#include <SDL2/SDL.h>
#include <memory>

struct SDLSetup {
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderTarget;
    SDLSetup();
};

#endif

#endif // MYAWESOMEGAME_SDL_SETUP_HPP
