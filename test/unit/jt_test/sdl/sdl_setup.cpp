#include "sdl_setup.hpp"
#include <render_target_lib.hpp>
#include <texture_manager_impl.hpp>
#include <sdl_2_include.hpp>
#include <iostream>

SDLSetup::SDLSetup()
{
    window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("unittests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 10, 10, 0),
        [](SDL_Window* w) { SDL_DestroyWindow(w); });
    m_renderTarget = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
        [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    if (!m_renderTarget) {
        throw std::logic_error { "failed to create renderer." };
    }
    SDL_SetRenderDrawBlendMode(m_renderTarget.get(), SDL_BLENDMODE_BLEND);

    TTF_Init();
}

std::shared_ptr<jt::RenderTargetLayer> getRenderTarget()
{
    static SDLSetup setup;
    return setup.m_renderTarget;
}

std::shared_ptr<jt::RenderTargetInterface> getRenderTargetContainer()
{
    auto target = std::make_shared<jt::RenderTarget>(getRenderTarget());
    return target;
}

jt::TextureManagerInterface& getTextureManager()
{
    static jt::TextureManagerImpl tm { getRenderTarget() };
    tm.reset();
    return tm;
}
