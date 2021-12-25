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

GameBase::GameBase(std::shared_ptr<jt::RenderWindowInterface> renderWindow,
    std::shared_ptr<InputManagerInterface> input, MusicPlayerInterface& musicPlayer,
    std::shared_ptr<CamInterface> camera, std::shared_ptr<StateManagerInterface> stateManager)
    : m_renderWindow { std::move(renderWindow) }
    , m_inputManager { std::move(input) }
    , m_camera { std::move(camera) }
    , m_musicPlayer { musicPlayer }
    , m_stateManager { std::move(stateManager) }
{
    if (m_renderWindow == nullptr) {
        throw std::invalid_argument { "render window DI for game can not be null" };
    }
    if (m_inputManager == nullptr) {
        throw std::invalid_argument { "input DI for game can not be null" };
    }
    if (m_camera == nullptr) {
        throw std::invalid_argument { "camera DI for game can not be null" };
    }
    if (m_stateManager == nullptr) {
        throw std::invalid_argument { "getStateManager DI for game can not be null" };
    }

    auto targetCout = std::make_shared<jt::LogTargetCout>();
    targetCout->setLogLevel(LogLevel::LogLevelInfo);
    m_logger.addLogTarget(targetCout);
    m_logger.addLogTarget(std::make_shared<jt::LogTargetFile>());
    m_logger.setLogLevel(LogLevel::LogLevelOff);
    m_actionCommandManager = std::make_shared<ActionCommandManager>(m_logger);
    m_logger.setLogLevel(LogLevel::LogLevelDebug);
}

void GameBase::runOneFrame()
{
    m_logger.verbose("runOneFrame", { "jt" });
    m_actionCommandManager->update();
    m_stateManager->checkAndPerformSwitchState(getPtr());

    auto const now = std::chrono::steady_clock::now();

    float const elapsed_in_seconds
        = std::chrono::duration_cast<std::chrono::microseconds>(now - m_timeLast).count() / 1000.0f
        / 1000.0f;
    m_timeLast = now;

    if (m_age != 0) {
        getCamera()->update(elapsed_in_seconds);
        update(elapsed_in_seconds);
        draw();
    }
    m_age++;
}

std::weak_ptr<GameInterface> GameBase::getPtr() { return shared_from_this(); }

void GameBase::reset()
{
    m_logger.info("Game reset", { "jt" });
    getCamera()->reset();
    input()->reset();
}

std::shared_ptr<jt::RenderWindowInterface> GameBase::getRenderWindow() const
{
    return m_renderWindow;
}

std::shared_ptr<InputManagerInterface> GameBase::input() { return m_inputManager; }

MusicPlayerInterface& GameBase::getMusicPlayer() { return m_musicPlayer; }

std::shared_ptr<CamInterface> GameBase::getCamera() { return m_camera; }
std::shared_ptr<CamInterface> GameBase::getCamera() const { return m_camera; }

std::shared_ptr<StateManagerInterface> GameBase::getStateManager() { return m_stateManager; }

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
