#include "game_base.hpp"
#include "camera.hpp"
#include "game_state.hpp"
#include "input/input_manager_interface.hpp"
#include "logging/log_target_cout.hpp"
#include "logging/logger.hpp"
#include "state_manager.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

namespace jt {

GameBase::GameBase(std::shared_ptr<jt::RenderWindowInterface> renderWindow,
    std::shared_ptr<InputManagerInterface> input, std::shared_ptr<MusicPlayerInterface> musicPlayer,
    std::shared_ptr<CamInterface> camera, std::shared_ptr<StateManagerInterface> stateManager)
    : m_renderWindow { std::move(renderWindow) }
    , m_inputManager { std::move(input) }
    , m_camera { std::move(camera) }
    , m_musicPlayer { std::move(musicPlayer) }
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
    if (m_musicPlayer == nullptr) {
        throw std::invalid_argument { "music player DI for game can not be null" };
    }
    if (m_stateManager == nullptr) {
        throw std::invalid_argument { "getStateManager DI for game can not be null" };
    }

    m_logger = std::make_shared<jt::Logger>();
    m_logger->setLogLevel(LogLevel::LogLevelDebug);
    auto targetCout = std::make_shared<jt::LogTargetCout>();
    targetCout->setLogLevel(LogLevel::LogLevelInfo);
    m_logger->addLogTarget(targetCout);
    // TODO Add file logging
}

void GameBase::run()
{
    try {
        getLogger()->verbose("run", { "jt" });
        m_stateManager->checkAndPerformSwitchState(getPtr());

        auto const now = std::chrono::steady_clock::now();

        float const elapsed_in_seconds
            = std::chrono::duration_cast<std::chrono::microseconds>(now - m_timeLast).count()
            / 1000.0f / 1000.0f;
        m_timeLast = now;

        if (m_age != 0) {
            getCamera()->update(elapsed_in_seconds);
            update(elapsed_in_seconds);
            draw();
        }
        m_age++;

    } catch (std::exception const& e) {
        std::cerr << "!! ERROR: Exception occurred !!\n";
        std::cerr << e.what() << std::endl;
        throw;
    }
}

std::weak_ptr<GameInterface> GameBase::getPtr() { return shared_from_this(); }

void GameBase::reset()
{
    m_logger->info("Game reset", { "jt" });
    getCamera()->reset();
    input()->reset();
}

std::shared_ptr<jt::RenderWindowInterface> GameBase::getRenderWindow() const
{
    return m_renderWindow;
}

std::shared_ptr<InputManagerInterface> GameBase::input() { return m_inputManager; }

std::shared_ptr<MusicPlayerInterface> GameBase::getMusicPlayer() { return m_musicPlayer; }

std::shared_ptr<CamInterface> GameBase::getCamera() { return m_camera; }
std::shared_ptr<CamInterface> GameBase::getCamera() const { return m_camera; }

std::shared_ptr<StateManagerInterface> GameBase::getStateManager() { return m_stateManager; }

std::shared_ptr<jt::renderTarget> GameBase::getRenderTarget() const { return m_renderTarget; }

std::shared_ptr<jt::TextureManagerInterface> GameBase::getTextureManager()
{
    return m_textureManager;
}

std::shared_ptr<jt::LoggerInterface> GameBase::getLogger() { return m_logger; }

} // namespace jt
