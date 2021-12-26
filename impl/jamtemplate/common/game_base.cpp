#include "game_base.hpp"
#include "action_commands/action_command_manager.hpp"
#include "camera.hpp"
#include "input/input_manager_interface.hpp"
#include "logging/log_target_cout.hpp"
#include "logging/log_target_file.hpp"
#include "logging/logger.hpp"
#include "state_manager.hpp"
#include <iostream>

namespace jt {

namespace {
// TODO make this a free function that the user can call
void createDefaultLogTargets(LoggerInterface& logger)
{
    auto targetCout = std::make_shared<LogTargetCout>();
    targetCout->setLogLevel(LogLevel::LogLevelInfo);

    logger.addLogTarget(targetCout);
    logger.addLogTarget(std::make_shared<LogTargetFile>());
    logger.setLogLevel(LogLevel::LogLevelDebug);
}
} // namespace

GameBase::GameBase(RenderWindowInterface& renderWindow, InputManagerInterface& input,
    MusicPlayerInterface& musicPlayer, CamInterface& camera, StateManagerInterface& stateManager,
    LoggerInterface& logger, ActionCommandManagerInterface& actionCommandManager)
    : m_renderWindow { renderWindow }
    , m_inputManager { input }
    , m_camera { camera }
    , m_musicPlayer { musicPlayer }
    , m_stateManager { stateManager }
    , m_logger { logger }
    , m_actionCommandManager { actionCommandManager }
{
    createDefaultLogTargets(m_logger);
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

std::shared_ptr<renderTarget> GameBase::getRenderTarget() const { return m_renderTarget; }

TextureManagerInterface& GameBase::getTextureManager() { return m_textureManager.value(); }

LoggerInterface& GameBase::getLogger() { return m_logger; }

ActionCommandManagerInterface& GameBase::getActionCommandManager()
{
    return m_actionCommandManager;
}

} // namespace jt
