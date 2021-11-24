#include "game_base.hpp"
#include "camera.hpp"
#include "game_state.hpp"
#include "input_manager_interface.hpp"
#include "state_manager.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

namespace jt {

GameBase::GameBase(
    std::shared_ptr<CamInterface> camera, std::shared_ptr<StateManagerInterface> stateManager)
    : m_camera { std::move(camera) }
    , m_stateManager { stateManager }
{
    if (m_camera == nullptr) {
        throw std::invalid_argument { "camera DI for game can not be null" };
    }
    if (m_stateManager == nullptr) {
        throw std::invalid_argument { "stateManager DI for game can not be null" };
    }
}

void GameBase::run()
{
    try {
        if (m_stateManager->checkForGameStateSwitch(getPtr())) {
            reset();
        }

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
    getCamera()->reset();
    input()->reset();
}

std::shared_ptr<CamInterface> GameBase::getCamera() { return m_camera; }
std::shared_ptr<CamInterface> GameBase::getCamera() const { return m_camera; }
std::shared_ptr<StateManagerInterface> GameBase::stateManager() { return m_stateManager; }

} // namespace jt
