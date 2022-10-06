#include "logging_state_manager.hpp"

jt::LoggingStateManager::LoggingStateManager(
    jt::StateManagerInterface& decoratee, jt::LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

std::shared_ptr<jt::GameState> jt::LoggingStateManager::getCurrentState()
{
    m_logger.verbose("getCurrentState", { "jt", "StateManager" });
    return m_decoratee.getCurrentState();
}
void jt::LoggingStateManager::setTransition(
    std::shared_ptr<jt::StateManagerTransitionInterface> transition)
{
    m_logger.info("setTransition", { "jt", "StateManager" });
    m_decoratee.setTransition(transition);
}

void jt::LoggingStateManager::switchState(std::shared_ptr<jt::GameState> newState)
{
    std::string stateName = "";
    if (newState) {
        stateName = ": " + newState->getName();
    }
    m_logger.info("SwitchState" + stateName, { "jt", "StateManager" });
    m_decoratee.switchState(newState);
}

void jt::LoggingStateManager::update(std::weak_ptr<jt::GameInterface> gameInstance, float elapsed)
{
    m_logger.verbose("update", { "jt", "StateManager" });
    m_decoratee.update(gameInstance, elapsed);
}

void jt::LoggingStateManager::draw(std::shared_ptr<jt::RenderTargetInterface> rt)
{
    m_logger.verbose("draw", { "jt", "StateManager" });
    m_decoratee.draw(rt);
}
std::shared_ptr<jt::StateManagerTransitionInterface> jt::LoggingStateManager::getTransition()
{
    m_logger.verbose("getTransition", { "jt", "StateManager" });
    return m_decoratee.getTransition();
}
