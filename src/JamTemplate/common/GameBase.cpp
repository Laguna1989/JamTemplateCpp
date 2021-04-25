﻿#include "GameBase.hpp"
#include "Camera.hpp"
#include "GameState.hpp"
#include "InputManagerInterface.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

namespace jt {

GameBase::GameBase()
    : m_state { nullptr }
    , m_nextState { nullptr }
    , m_camera { std::make_shared<Camera>() }
{
}

void GameBase::switchState(std::shared_ptr<GameState> newState)
{
    if (newState == nullptr) {
        throw std::invalid_argument { "cannot switch to nullptr state!" };
    }
    m_nextState = newState;
    // if no state has been assigned yet, we can directly switch state here.
    if (m_state == nullptr) {
        doSwitchState();
    }
}

std::shared_ptr<GameState> GameBase::getCurrentSate()
{
    if (m_nextState == nullptr) {
        return m_state;
    }
    return m_nextState;
}

void GameBase::run()
{
    try {
        if (m_nextState != nullptr) {
            doSwitchState();
            return;
        }
        if (m_state == nullptr) {
            return;
        }

        auto const now = std::chrono::steady_clock::now();

        float const elapsed_in_seconds
            = std::chrono::duration_cast<std::chrono::microseconds>(now - m_timeLast).count()
            / 1000.0f / 1000.0f;
        m_timeLast = now;

        if (m_age != 0) {
            updateShake(elapsed_in_seconds);
            update(elapsed_in_seconds);
            draw();
        }
        m_age++;

    } catch (std::exception const& e) {
        std::cerr << "!! ERROR: Exception ocurred !!\n";
        std::cerr << e.what() << std::endl;
        throw;
    } catch (...) {
        std::cerr << "!! ERROR: Unhandled Exception ocurred !!\n";
        std::terminate();
    }
}

std::weak_ptr<GameInterface> GameBase::getPtr() { return shared_from_this(); }

void GameBase::doSwitchState()
{
    m_state = m_nextState;
    m_nextState = nullptr;

    getCamera()->reset();
    m_state->setGameInstance(getPtr());
    m_state->create();
    if (input()) {
        input()->reset();
    }
}

std::shared_ptr<CamInterface> GameBase::getCamera() { return m_camera; }
std::shared_ptr<CamInterface> GameBase::getCamera() const { return m_camera; }

} // namespace jt
