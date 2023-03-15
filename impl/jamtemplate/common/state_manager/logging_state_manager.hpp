#ifndef JAMTEMPLATE_LOGGING_STATE_MANAGER_HPP
#define JAMTEMPLATE_LOGGING_STATE_MANAGER_HPP

#include <log/logger_interface.hpp>
#include <state_manager/state_manager_interface.hpp>
namespace jt {
class LoggingStateManager : public StateManagerInterface {
public:
    LoggingStateManager(StateManagerInterface& decoratee, LoggerInterface& logger);

    std::shared_ptr<GameState> getCurrentState() override;
    void setTransition(std::shared_ptr<StateManagerTransitionInterface> transition) override;
    void switchState(std::shared_ptr<GameState> newState) override;
    void switchToStoredState(std::string const& identifier) override;
    void update(std::weak_ptr<GameInterface> gameInstance, float elapsed) override;
    void draw(std::shared_ptr<jt::RenderTargetInterface> rt) override;

    std::shared_ptr<StateManagerTransitionInterface> getTransition() override;

    void storeCurrentState(std::string const& identifier) override;
    std::shared_ptr<jt::GameState> getStoredState(std::string const& identifier) override;
    void clearStoredState(std::string const& identifier) override;

    std::vector<std::string> getStoredStateIdentifiers() const override;

private:
    StateManagerInterface& m_decoratee;
    LoggerInterface& m_logger;
};

} // namespace jt

#endif // JAMTEMPLATE_LOGGING_STATE_MANAGER_HPP
