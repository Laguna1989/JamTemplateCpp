#ifndef JAMTEMPLATE_SDL_SETUP_HPP
#define JAMTEMPLATE_SDL_SETUP_HPP

#include <render_target.hpp>
#include <texture_manager_interface.hpp>
#include <SDL2/SDL.h>
#include <memory>

struct SDLSetup {
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> RenderTarget;
    SDLSetup();
};

std::shared_ptr<jt::RenderTarget> getRenderTarget();
jt::TextureManagerInterface& getTextureManager();

#endif // JAMTEMPLATE_SDL_SETUP_HPP
