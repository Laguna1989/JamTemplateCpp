#include "game.hpp"

#include <sdl_2_include.hpp>

#ifdef JT_ENABLE_WEB
#include <emscripten.h>
#endif

namespace jt {

Game::Game(GfxInterface& gfx, InputManagerInterface& input, AudioInterface& audio,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager, CacheInterface& cache)
    : GameBase { gfx, input, audio, stateManager, logger, actionCommandManager, cache }
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    m_logger.info("Connected gamepads: " + std::to_string(SDL_NumJoysticks()));
    TTF_Init();

    m_logger.debug("Game constructor done", { "jt", "game" });
}

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    m_logger.debug("start game", { "jt", "game" });
#ifdef JT_ENABLE_WEB
    emscripten_set_main_loop(gameloop_function, 0, 1);
#else
    while (gfx().window().isOpen()) {
        gameloop_function();
    }
#endif
}

} // namespace jt
