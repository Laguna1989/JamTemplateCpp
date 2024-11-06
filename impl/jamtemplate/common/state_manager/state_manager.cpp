#include "state_manager.hpp"
#include "performance_measurement.hpp"
#include <game_interface.hpp>
#include <state_manager/state_manager_transition_none.hpp>
#include <tracy/Tracy.hpp>
#include <stdexcept>

jt::StateManager::StateManager(std::shared_ptr<jt::GameState> initialState)
    : m_currentState { nullptr }
    , m_nextState { initialState }
{
    m_transition = std::make_shared<jt::StateManagerTransitionNone>();
}

std::shared_ptr<jt::GameState> jt::StateManager::getCurrentState() { return m_currentState; }

void jt::StateManager::switchState(std::shared_ptr<jt::GameState> newState)
{
    if (newState == nullptr) [[unlikely]] {
        throw std::invalid_argument { "cannot switch to nullptr state!" };
    }
    m_nextState = newState;
    getTransition()->start();
    getTransition()->update(0.00f);
}

void jt::StateManager::switchToStoredState(std::string const& identifier)
{
    if (!m_storedStates.contains(identifier)) {
        throw std::invalid_argument { "no state stored with identifier: " + identifier };
    }

    switchState(m_storedStates[identifier]);
}

void jt::StateManager::doSwitchState(std::weak_ptr<jt::GameInterface> gameInstance)
{
    if (!m_nextState->hasBeenInitialized()) {
        std::shared_ptr<GameInterface> g = gameInstance.lock();
        if (g) {
            g->reset();
        }
        m_nextState->setGameInstance(gameInstance);
        m_nextState->create();
    }

    m_nextState->enter();

    m_currentState = m_nextState;
    m_nextState = nullptr;
}

void jt::StateManager::update(std::weak_ptr<jt::GameInterface> gameInstance, float elapsed)
{
    ZoneScopedN("jt::StateManager::update");
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
    ZoneScopedN("jt::StateManager::draw");
    getCurrentState()->draw();
    if (getTransition()->isInProgress()) {
        getTransition()->draw(rt);
    }
}

void jt::StateManager::storeCurrentState(std::string const& identifier)
{
    m_storedStates[identifier] = getCurrentState();
}

std::shared_ptr<jt::GameState> jt::StateManager::getStoredState(std::string const& identifier)
{
    if (!m_storedStates.contains(identifier)) {
        return nullptr;
    }
    return m_storedStates[identifier];
}

void jt::StateManager::clearStoredState(std::string const& identifier)
{
    m_storedStates.erase(identifier);
}

std::vector<std::string> jt::StateManager::getStoredStateIdentifiers() const
{
    std::vector<std::string> identifiers;
    for (auto const& kvp : m_storedStates) {
        identifiers.push_back(kvp.first);
    }
    return identifiers;
}
