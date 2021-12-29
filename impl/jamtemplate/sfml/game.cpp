#include "game.hpp"

namespace jt {

Game::Game(GfxInterface& gfx, InputManagerInterface& input, MusicPlayerInterface& musicPlayer,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : GameBase { gfx, input, musicPlayer, stateManager, logger, actionCommandManager }
{
    m_logger.debug("Game constructor done", { "jt" });
}

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    m_logger.debug("startGame", { "jt" });
    while (gfx().window().isOpen()) {
        gfx().window().checkForClose();
        gameloop_function();
    }
}

void Game::doUpdate(float const elapsed)
{
    m_logger.verbose("update game, elapsed=" + std::to_string(elapsed), { "jt" });
    getStateManager().getCurrentState()->update(elapsed);

    gfx().update(elapsed);

    jt::Vector2f const mpf = gfx().window().getMousePosition() / gfx().camera().getZoom();

    input().update(MousePosition { mpf.x + gfx().camera().getCamOffset().x,
                       mpf.y + gfx().camera().getCamOffset().y, mpf.x, mpf.y },
        elapsed);
}

void Game::doDraw() const
{
    m_logger.verbose("draw game", { "jt" });
    auto target = gfx().target();
    if (!target) {
        return;
    }

    target->clear(sf::Color::Black);

    m_stateManager.getCurrentState()->draw();

    gfx().display();
}

} // namespace jt
