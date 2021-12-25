#include "game_base.hpp"
#include "action_commands/action_command_manager.hpp"
#include "camera.hpp"
#include "input/input_manager_interface.hpp"
#include "logging/log_target_cout.hpp"
#include "logging/log_target_file.hpp"
#include "logging/logger.hpp"
#include "state_manager.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

namespace jt {

GameBase::GameBase(RenderWindowInterface& renderWindow, InputManagerInterface& input,
    MusicPlayerInterface& musicPlayer, CamInterface& camera, StateManagerInterface& stateManager)
    : m_renderWindow { renderWindow }
    , m_inputManager { input }
    , m_camera { camera }
    , m_musicPlayer { musicPlayer }
    , m_stateManager { stateManager }
{
    // TODO move this out into a separate dependency
    createDefaultLogTargets();
}
void GameBase::createDefaultLogTargets()
{
    auto targetCout = std::make_shared<LogTargetCout>();
    targetCout->setLogLevel(LogLevel::LogLevelInfo);
    m_logger.addLogTarget(targetCout);
    m_logger.addLogTarget(std::make_shared<LogTargetFile>());
    m_logger.setLogLevel(LogLevel::LogLevelOff);
    m_actionCommandManager = std::make_shared<ActionCommandManager>(m_logger);
    m_logger.setLogLevel(LogLevel::LogLevelDebug);
}

void GameBase::runOneFrame()
{
    m_logger.verbose("runOneFrame", { "jt" });
    m_actionCommandManager->update();
    m_stateManager.checkAndPerformSwitchState(getPtr());

    auto const now = std::chrono::steady_clock::now();

    float const elapsed_in_seconds
        = std::chrono::duration_cast<std::chrono::microseconds>(now - m_timeLast).count() / 1000.0f
        / 1000.0f;
    m_timeLast = now;

    if (m_age != 0) {
        getCamera().update(elapsed_in_seconds);
        update(elapsed_in_seconds);
        draw();
    }
    m_age++;
}

std::weak_ptr<GameInterface> GameBase::getPtr() { return shared_from_this(); }

void GameBase::reset()
{
    m_logger.info("Game reset", { "jt" });
    getCamera().reset();
    input().reset();
}

RenderWindowInterface& GameBase::getRenderWindow() const { return m_renderWindow; }

InputManagerInterface& GameBase::input() { return m_inputManager; }

MusicPlayerInterface& GameBase::getMusicPlayer() { return m_musicPlayer; }

CamInterface& GameBase::getCamera() { return m_camera; }
CamInterface& GameBase::getCamera() const { return m_camera; }

StateManagerInterface& GameBase::getStateManager() { return m_stateManager; }

std::shared_ptr<jt::renderTarget> GameBase::getRenderTarget() const { return m_renderTarget; }

std::shared_ptr<jt::TextureManagerInterface> GameBase::getTextureManager()
{
    return m_textureManager;
}

LoggerInterface& GameBase::getLogger() { return m_logger; }
std::shared_ptr<jt::ActionCommandManagerInterface> GameBase::getActionCommandManager()
{
    return m_actionCommandManager;
}

} // namespace jt
