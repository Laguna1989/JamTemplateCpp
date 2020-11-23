#include "GameBase.hpp"
#include "GameState.hpp"
#include <exception>
#include <stdexcept>

namespace JamTemplate {

GameBase::GameBase()
    : m_state { nullptr }
    , m_nextState { nullptr }
{
}

void GameBase::switchState(std::shared_ptr<GameState> newState)
{
    // std::cout << "switchstate\n";
    if (newState == nullptr) {
        throw std::invalid_argument { "cannot switch to nullptr state!" };
    }
    m_nextState = newState;
    // if no state has been assigned yet, we can directly switch state here.
    if (m_state == nullptr) {
        doSwitchState();
    }
}

void GameBase::run()
{
    if (m_nextState != nullptr) {
        doSwitchState();
        return;
    }
    if (m_state == nullptr) {
        return;
    }
    auto const now = std::chrono::steady_clock::now();

    float const elapsed
        = std::chrono::duration_cast<std::chrono::microseconds>(now - timeLast).count() / 1000.0f
        / 1000.0f;
    timeLast = now;
    if (m_age != 0) {
        updateShake(elapsed);
        m_state->update(elapsed);

        update(elapsed);
        draw();
    }
    m_age++;
}

jt::vector2 GameBase::getCamOffset() { return m_CamOffset; }

void GameBase::setCamOffset(jt::vector2 const& ofs) { m_CamOffset = ofs; }
void GameBase::moveCam(jt::vector2 const& v) { m_CamOffset = m_CamOffset + v; }

void GameBase::shake(float t, float strength, float shakeInterval)
{
    m_shakeTimer = t;
    m_shakeStrength = strength;
    m_shakeInterval = m_shakeIntervalMax = shakeInterval;
}

std::weak_ptr<GameBase> GameBase::getPtr() { return shared_from_this(); }

void GameBase::doSwitchState()
{
    m_state = m_nextState;
    m_nextState = nullptr;

    m_CamOffset = jt::vector2 { 0.0f, 0.0f };
    m_state->setGameInstance(getPtr());
    m_state->create();
    // TODO
    // JamTemplate::InputManager::reset();
    resetShake();
}

} // namespace JamTemplate
