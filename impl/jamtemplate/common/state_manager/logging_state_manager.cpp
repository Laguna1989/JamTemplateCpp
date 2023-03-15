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
    m_logger.info("Switch GameState to new state: " + stateName, { "jt", "StateManager" });
    m_decoratee.switchState(newState);
}
void jt::LoggingStateManager::switchToStoredState(std::string const& identifier)
{
    m_logger.info("Switch GameState to stored state: " + identifier, { "jt", "StateManager" });
    auto const state = m_decoratee.getStoredState(identifier);
    if (state == nullptr) {
        m_logger.error("Switch GameState to stored State not possible, because no state saved with "
                       "identifier '"
                + identifier + "'",
            { "jt", "StateManager" });
    }
    m_decoratee.switchToStoredState(identifier);
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
void jt::LoggingStateManager::storeCurrentState(std::string const& identifier)
{
    m_logger.debug("store gamestate '" + identifier + "'", { "jt", "StateManager" });
    m_decoratee.storeCurrentState(identifier);
}
std::shared_ptr<jt::GameState> jt::LoggingStateManager::getStoredState(
    std::string const& identifier)
{
    m_logger.debug("retrieve gamestate '" + identifier + "'", { "jt", "StateManager" });
    return m_decoratee.getStoredState(identifier);
}
void jt::LoggingStateManager::clearStoredState(std::string const& identifier)
{
    m_logger.debug("clear gamestate '" + identifier + "'", { "jt", "StateManager" });
    m_decoratee.clearStoredState(identifier);
}
std::vector<std::string> jt::LoggingStateManager::getStoredStateIdentifiers() const
{
    return m_decoratee.getStoredStateIdentifiers();
}
