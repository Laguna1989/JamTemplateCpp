#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>

#ifdef JT_ENABLE_WEB
#include <emscripten.h>
#endif

namespace jt {

Game::Game(GfxInterface& gfx, InputManagerInterface& input, MusicPlayerInterface& musicPlayer,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : GameBase { gfx, input, musicPlayer, stateManager, logger, actionCommandManager }
{
    TTF_Init();

    // important fix for SDL_Mixer: OpenAudio has to be called before Mix_Init,
    // otherwise ogg is not supported.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        m_logger.fatal("OpenAudio failed", { "jt" });
    }
    if (Mix_Init(MIX_INIT_OGG) != 0) {
        m_logger.fatal("Mix_Init failed", { "jt" });
    }
    m_logger.debug("Game constructor done", { "jt" });
}

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    m_logger.debug("startGame", { "jt" });
#ifdef JT_ENABLE_WEB
    emscripten_set_main_loop(gameloop_function, 0, 1);
#else
    while (gfx().window().isOpen()) {
        gameloop_function();
    }
#endif
}

} // namespace jt
