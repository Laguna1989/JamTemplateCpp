#include "state_manager.hpp"
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
}

void StateManager::doSwitchState(std::weak_ptr<GameInterface> gameInstance)
{
    m_nextState->setGameInstance(gameInstance);
    m_nextState->create();

    m_state = m_nextState;
    m_nextState = nullptr;
}

bool StateManager::checkForGameStateSwitch(std::weak_ptr<GameInterface> gameInstace)
{
    if (m_nextState != nullptr) {
        doSwitchState(gameInstace);
        return true;
    }
    return false;
}
std::shared_ptr<GameState> StateManager::getNextState() { return m_nextState; }

} // namespace jt