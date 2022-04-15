#include "sdl_setup.hpp"
#include <texture_manager_impl.hpp>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>

SDLSetup::SDLSetup()
{
    window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("unittests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 10, 10, 0),
        [](SDL_Window* w) { SDL_DestroyWindow(w); });
    RenderTarget = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
        [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    if (!RenderTarget) {
        throw std::logic_error { "failed to create renderer." };
    }
    SDL_SetRenderDrawBlendMode(RenderTarget.get(), SDL_BLENDMODE_BLEND);

    TTF_Init();
}

std::shared_ptr<jt::RenderTarget> getRenderTarget()
{
    static SDLSetup setup;
    return setup.RenderTarget;
}

jt::TextureManagerInterface& getTextureManager()
{
    static jt::TextureManagerImpl tm { getRenderTarget() };
    tm.reset();
    return tm;
}
