#ifndef JAMTEMPLATE_STATE_MANAGER_HPP
#define JAMTEMPLATE_STATE_MANAGER_HPP

#include <game_state.hpp>
#include <state_manager/state_manager_interface.hpp>
#include <map>
#include <memory>

namespace jt {

class GameInterface;

class StateManager : public StateManagerInterface {
public:
    explicit StateManager(std::shared_ptr<GameState> initialState);
    std::shared_ptr<GameState> getCurrentState() override;
    std::shared_ptr<GameState> getNextState();

    void switchState(std::shared_ptr<GameState> newState) override;
    void switchToStoredState(std::string const& identifier) override;

    void update(std::weak_ptr<GameInterface> gameInstance, float elapsed) override;

    void draw(std::shared_ptr<jt::RenderTargetInterface> rt) override;

    void setTransition(std::shared_ptr<StateManagerTransitionInterface> transition) override;

    std::shared_ptr<StateManagerTransitionInterface> getTransition() override;

    void storeCurrentState(std::string const& identifier) override;
    std::shared_ptr<jt::GameState> getStoredState(std::string const& identifier) override;
    void clearStoredState(std::string const& identifier) override;

    std::vector<std::string> getStoredStateIdentifiers() const override;

private:
    std::shared_ptr<GameState> m_currentState { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };
    std::shared_ptr<StateManagerTransitionInterface> m_transition { nullptr };

    std::map<std::string, std::shared_ptr<jt::GameState>> m_storedStates;

    void doSwitchState(std::weak_ptr<GameInterface> gameInstance);
};
} // namespace jt

#endif // JAMTEMPLATE_STATE_MANAGER_HPP
