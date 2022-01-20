#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>

#ifdef JT_ENABLE_WEB
#include <emscripten.h>
#endif

namespace jt {

Game::Game(GfxInterface& gfx, InputManagerInterface& input, AudioInterface& audio,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : GameBase { gfx, input, audio, stateManager, logger, actionCommandManager }
{
    TTF_Init();

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
