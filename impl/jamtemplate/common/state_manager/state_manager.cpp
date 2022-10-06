#include "state_manager.hpp"
#include <game_interface.hpp>
#include <state_manager/state_manager_transition_none.hpp>
#include <stdexcept>

jt::StateManager::StateManager(std::shared_ptr<jt::GameState> initialState)
    : m_state { nullptr }
    , m_nextState { initialState }
{
    m_transition = std::make_shared<jt::StateManagerTransitionNone>();
}

std::shared_ptr<jt::GameState> jt::StateManager::getCurrentState() { return m_state; }

void jt::StateManager::switchState(std::shared_ptr<jt::GameState> newState)
{
    if (newState == nullptr) {
        throw std::invalid_argument { "cannot switch to nullptr state!" };
    }
    m_nextState = newState;
    getTransition()->start();
    getTransition()->update(0.00f);
}

void jt::StateManager::doSwitchState(std::weak_ptr<jt::GameInterface> gameInstance)
{
    std::shared_ptr<GameInterface> g = gameInstance.lock();
    if (g) {
        g->reset();
    }
    m_nextState->setGameInstance(gameInstance);
    m_nextState->create();

    m_state = m_nextState;
    m_nextState = nullptr;
}

void jt::StateManager::update(std::weak_ptr<jt::GameInterface> gameInstance, float elapsed)
{
    getTransition()->update(elapsed);
    if (m_nextState != nullptr) {
        if (getTransition()->triggerStateChange()) {
            doSwitchState(gameInstance);
        }
    }

    getCurrentState()->update(elapsed);
}

std::shared_ptr<jt::GameState> jt::StateManager::getNextState() { return m_nextState; }

void jt::StateManager::setTransition(
    std::shared_ptr<jt::StateManagerTransitionInterface> transition)
{
    m_transition = transition;
}

std::shared_ptr<jt::StateManagerTransitionInterface> jt::StateManager::getTransition()
{
    static std::shared_ptr<StateManagerTransitionNone> defaultTransition {
        std::make_shared<StateManagerTransitionNone>()
    };

    return (m_transition == nullptr) ? defaultTransition : m_transition;
}

void jt::StateManager::draw(std::shared_ptr<jt::RenderTargetInterface> rt)
{
    getCurrentState()->draw();
    if (getTransition()->isInProgress()) {
        getTransition()->draw(rt);
    }
}
