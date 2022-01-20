#include "game.hpp"

namespace jt {

Game::Game(GfxInterface& gfx, InputManagerInterface& input, AudioInterface& audio,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : GameBase { gfx, input, audio, stateManager, logger, actionCommandManager }
{
    m_logger.debug("Game constructor done", { "jt" });
}

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    m_logger.debug("startGame", { "jt" });
    while (gfx().window().isOpen()) {
        gameloop_function();
    }
}

} // namespace jt
