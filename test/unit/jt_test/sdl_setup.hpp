#ifndef GUARD_JAMTEMAPLTE_SDL_SETUP_HPP
#define GUARD_JAMTEMAPLTE_SDL_SETUP_HPP

#include "render_target.hpp"
#include "texture_manager_interface.hpp"
#include <memory>

#if !USE_SFML
#include <SDL2/SDL.h>

struct SDLSetup {
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> RenderTarget;
    SDLSetup();
};

#endif

std::shared_ptr<jt::RenderTarget> getRenderTarget();
jt::TextureManagerInterface& getTextureManager();

#endif // GUARD_JAMTEMAPLTE_SDL_SETUP_HPP
