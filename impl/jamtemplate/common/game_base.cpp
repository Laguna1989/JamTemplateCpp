#include "game_base.hpp"

namespace jt {

GameBase::GameBase(GfxInterface& gfx, InputManagerInterface& input, AudioInterface& audio,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : m_gfx { gfx }
    , m_inputManager { input }
    , m_audio { audio }
    , m_stateManager { stateManager }
    , m_logger { logger }
    , m_actionCommandManager { actionCommandManager }
{
}

void GameBase::runOneFrame()
{
    m_logger.verbose("runOneFrame", { "jt" });
    m_actionCommandManager.update();

    auto const now = std::chrono::steady_clock::now();

    float const elapsed_in_seconds
        = std::chrono::duration_cast<std::chrono::microseconds>(now - m_timeLast).count() / 1000.0f
        / 1000.0f;
    m_timeLast = now;

    if (m_age != 0) {
        gfx().window().checkForClose();
        update(elapsed_in_seconds);
        draw();
    }
    m_age++;
}

std::weak_ptr<GameInterface> GameBase::getPtr() { return shared_from_this(); }

void GameBase::reset()
{
    m_logger.info("Game reset", { "jt" });
    gfx().reset();
    input().reset();
}

GfxInterface& GameBase::gfx() const { return m_gfx; }

InputManagerInterface& GameBase::input() { return m_inputManager; }

AudioInterface& GameBase::audio() { return m_audio; }

StateManagerInterface& GameBase::getStateManager() { return m_stateManager; }

LoggerInterface& GameBase::getLogger() { return m_logger; }

ActionCommandManagerInterface& GameBase::getActionCommandManager()
{
    return m_actionCommandManager;
}

void GameBase::doUpdate(float const elapsed)
{
    m_logger.verbose("update game, elapsed=" + std::to_string(elapsed), { "jt" });
    m_stateManager.update(getPtr(), elapsed);
    m_audio.update();
    gfx().update(elapsed);

    jt::Vector2f const mpf = gfx().window().getMousePosition() / gfx().camera().getZoom();

    input().update(MousePosition { mpf.x + gfx().camera().getCamOffset().x,
                       mpf.y + gfx().camera().getCamOffset().y, mpf.x, mpf.y },
        elapsed);
}

void GameBase::doDraw() const
{
    m_logger.verbose("draw game", { "jt" });

    gfx().clear();
    m_stateManager.draw(gfx().target());
    gfx().display();
}

} // namespace jt
