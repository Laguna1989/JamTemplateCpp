#include "game_base.hpp"
#include "action_commands/action_command_manager.hpp"
#include "input/input_manager_interface.hpp"
#include "logging/logger.hpp"
#include "state_manager.hpp"

namespace jt {

GameBase::GameBase(GfxInterface& gfx, InputManagerInterface& input,
    MusicPlayerInterface& musicPlayer, StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : m_gfx { gfx }
    , m_inputManager { input }
    , m_musicPlayer { musicPlayer }
    , m_stateManager { stateManager }
    , m_logger { logger }
    , m_actionCommandManager { actionCommandManager }
{
}

void GameBase::runOneFrame()
{
    m_logger.verbose("runOneFrame", { "jt" });
    m_actionCommandManager.update();
    m_stateManager.checkAndPerformSwitchState(getPtr());

    auto const now = std::chrono::steady_clock::now();

    float const elapsed_in_seconds
        = std::chrono::duration_cast<std::chrono::microseconds>(now - m_timeLast).count() / 1000.0f
        / 1000.0f;
    m_timeLast = now;

    if (m_age != 0) {
        gfx().camera().update(elapsed_in_seconds);
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

MusicPlayerInterface& GameBase::getMusicPlayer() { return m_musicPlayer; }

StateManagerInterface& GameBase::getStateManager() { return m_stateManager; }

LoggerInterface& GameBase::getLogger() { return m_logger; }

ActionCommandManagerInterface& GameBase::getActionCommandManager()
{
    return m_actionCommandManager;
}

} // namespace jt
