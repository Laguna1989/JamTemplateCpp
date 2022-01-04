#include "state_manager.hpp"
#include "game_interface.hpp"
#include "state_manager_transition_none.hpp"
#include <stdexcept>
namespace jt {

StateManager::StateManager(std::shared_ptr<GameState> initialState)
    : m_state { nullptr }
    , m_nextState { initialState }
{
}

std::shared_ptr<GameState> StateManager::getCurrentState() { return m_state; }

void StateManager::switchState(std::shared_ptr<GameState> newState)
{
    if (newState == nullptr) {
        throw std::invalid_argument { "cannot switch to nullptr state!" };
    }
    m_nextState = newState;
    getTransition()->start();
    getTransition()->update(0.00f);
}

void StateManager::doSwitchState(std::weak_ptr<GameInterface> gameInstance)
{
    std::shared_ptr<GameInterface> g = gameInstance.lock();
    if (g) {
        g->reset();
    }
    g->getLogger().info("SwitchState", { "jt" });
    m_nextState->setGameInstance(gameInstance);
    m_nextState->create();

    m_state = m_nextState;
    m_nextState = nullptr;
}

void StateManager::update(std::weak_ptr<GameInterface> gameInstance, float elapsed)
{
    getTransition()->update(elapsed);
    if (m_nextState != nullptr) {
        if (getTransition()->triggerStateChange()) {
            doSwitchState(gameInstance);
        }
    }

    getCurrentState()->update(elapsed);
}

std::shared_ptr<GameState> StateManager::getNextState() { return m_nextState; }

void StateManager::setTransition(std::shared_ptr<StateManagerTransitionInterface> transition)
{
    m_transition = transition;
}

std::shared_ptr<StateManagerTransitionInterface> StateManager::getTransition()
{
    static std::shared_ptr<StateManagerTransitionNone> defaultTransition {
        std::make_shared<StateManagerTransitionNone>()
    };

    return (m_transition == nullptr) ? defaultTransition : m_transition;
}

void StateManager::draw(std::shared_ptr<RenderTarget> rt)
{
    getCurrentState()->draw();
    if (getTransition()->isInProgress()) {
        getTransition()->draw(rt);
    }
}

} // namespace jt
