#include "game.hpp"

jt::Game::Game(GfxInterface& gfx, InputManagerInterface& input, AudioInterface& audio,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager, jt::CacheInterface& cache)
    : GameBase { gfx, input, audio, stateManager, logger, actionCommandManager, cache }
{
    m_logger.debug("Game constructor done", { "jt", "game" });
}

void jt::Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    m_logger.debug("start game", { "jt", "game" });
    while (gfx().window().isOpen()) {
        gameloop_function();
    }
}
