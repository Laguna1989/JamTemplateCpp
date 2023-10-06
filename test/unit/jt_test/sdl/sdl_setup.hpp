#ifndef JAMTEMPLATE_SDL_SETUP_HPP
#define JAMTEMPLATE_SDL_SETUP_HPP

#include <graphics/render_target_interface.hpp>
#include <texture_manager_interface.hpp>
#include <sdl_2_include.hpp>
#include <memory>

struct SDLSetup {
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> m_renderTarget;
    SDLSetup();
};

std::shared_ptr<jt::RenderTargetLayer> getRenderTarget();
std::shared_ptr<jt::RenderTargetInterface> getRenderTargetContainer();
jt::TextureManagerInterface& getTextureManager();

#endif // JAMTEMPLATE_SDL_SETUP_HPP
