#include "game.hpp"
#include "action_commands/basic_action_commands.hpp"
#include "drawable_impl.hpp"
#include "game_state.hpp"
#include "input/input_manager.hpp"
#include "random/random.hpp"
#include "rect.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#ifdef JT_ENABLE_WEB
#include <emscripten.h>
#endif

namespace jt {

Game::Game(GfxInterface& gfx, InputManagerInterface& input, MusicPlayerInterface& musicPlayer,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : GameBase { gfx, input, musicPlayer, stateManager, logger, actionCommandManager }
{
    auto const width = gfx.window().getSize().x;
    auto const height = gfx.window().getSize().y;

    auto const scaledWidth = static_cast<int>(width / gfx.camera().getZoom());
    auto const scaledHeight = static_cast<int>(height / gfx.camera().getZoom());
    m_srcRect = jt::Recti { 0, 0, scaledWidth, scaledHeight };
    m_destRect = jt::Recti { 0, 0, static_cast<int>(width), static_cast<int>(height) };

    TTF_Init();

    // important fix for SDL_Mixer: OpenAudio has to be called before Mix_Init,
    // otherwise ogg is not supported.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        std::cout << "cannot OpenAudio: " << Mix_GetError() << std::endl;
    }
    if (Mix_Init(MIX_INIT_OGG) != 0) {
        std::cout << "cannot Mix_Init: " << Mix_GetError() << std::endl;
    }
    m_logger.debug("Game constructor done", { "jt" });
}

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
#ifdef JT_ENABLE_WEB
    emscripten_set_main_loop(gameloop_function, 0, 1);
#else
    while (gfx().window().isOpen()) {
        gameloop_function();
    }
#endif
}

void Game::doUpdate(float const elapsed)
{
    gfx().window().checkForClose();
    getStateManager().getCurrentState()->update(elapsed);
    gfx().camera().update(elapsed);

    jt::Vector2f const mpf = gfx().window().getMousePosition() / gfx().camera().getZoom();

    input().update(MousePosition { mpf.x + gfx().camera().getCamOffset().x,
                       mpf.y + gfx().camera().getCamOffset().y, mpf.x, mpf.y },
        elapsed);

    DrawableImpl::setCamOffset(-1.0f * gfx().camera().getCamOffset());
};

void Game::doDraw() const
{
    auto target = gfx().target().get();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    // for reasons this can not be a member.
    auto* const t = SDL_CreateTexture(target, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        static_cast<int>(m_srcRect.width), static_cast<int>(m_srcRect.height));

    // render to the small texture first
    SDL_SetRenderTarget(target, t);
    SDL_RenderClear(target);
    m_stateManager.getCurrentState()->draw();

    // Detach the texture
    SDL_SetRenderTarget(target, nullptr);

    // Now render the texture target to our screen
    SDL_RenderClear(target);
    SDL_Rect sourceRect { m_srcRect.left, m_srcRect.top, m_srcRect.width, m_srcRect.height };
    SDL_Rect destRect { static_cast<int>(gfx().camera().getShakeOffset().x),
        static_cast<int>(gfx().camera().getShakeOffset().y), m_destRect.width, m_destRect.height };
    SDL_RenderCopyEx(target, t, &sourceRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
    gfx().display();
    SDL_RenderPresent(target);

    SDL_DestroyTexture(t);
};

} // namespace jt
