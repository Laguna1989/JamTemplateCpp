#include <gtest/gtest.h>
#include <texture_manager.hpp>

#if USE_SDL
#include "texture_manager.hpp"
#include <SDL2/SDL.h>
std::shared_ptr<SDL_Window> window { nullptr };
std::shared_ptr<SDL_Renderer> renderTarget { nullptr };

#endif

int main(int argc, char** argv)
{
#if USE_SDL
    window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("unittests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 10, 10, 0),
        [](SDL_Window* w) { SDL_DestroyWindow(w); });
    renderTarget = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
        [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    if (!renderTarget) {
        throw std::logic_error { "failed to create renderer." };
    }
    SDL_SetRenderDrawBlendMode(renderTarget.get(), SDL_BLENDMODE_BLEND);
    jt::TextureManager::setRenderer(renderTarget);
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
