#include "logging_state_manager.hpp"

namespace jt {

LoggingStateManager::LoggingStateManager(StateManagerInterface& decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

std::shared_ptr<GameState> LoggingStateManager::getCurrentState()
{
    m_logger.verbose("getCurrentState", { "jt", "StateManager" });
    return m_decoratee.getCurrentState();
}
void LoggingStateManager::setTransition(std::shared_ptr<StateManagerTransitionInterface> transition)
{
    m_logger.info("setTransition", { "jt", "StateManager" });
    m_decoratee.setTransition(transition);
}

void LoggingStateManager::switchState(std::shared_ptr<GameState> newState)
{
    std::string stateName = "";
    if (newState) {
        stateName = ": " + newState->getName();
    }
    m_logger.info("SwitchState" + stateName, { "jt", "StateManager" });
    m_decoratee.switchState(newState);
}

void LoggingStateManager::update(std::weak_ptr<GameInterface> gameInstance, float elapsed)
{
    m_logger.verbose("update", { "jt", "StateManager" });
    m_decoratee.update(gameInstance, elapsed);
}

void LoggingStateManager::draw(std::shared_ptr<RenderTarget> rt)
{
    m_logger.verbose("draw", { "jt", "StateManager" });
    m_decoratee.draw(rt);
}

} // namespace jt
