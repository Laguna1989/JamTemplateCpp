#ifndef GUARD_JAMTEMAPLTE_STATE_MANAGER_HPP
#define GUARD_JAMTEMAPLTE_STATE_MANAGER_HPP

#include "game_state.hpp"
#include "state_manager_interface.hpp"
#include <memory>

namespace jt {

class GameInterface;

class StateManager : public StateManagerInterface {
public:
    StateManager(std::shared_ptr<GameState> initialState);
    std::shared_ptr<GameState> getCurrentState() override;
    std::shared_ptr<GameState> getNextState();

    void switchState(std::shared_ptr<GameState> newState) override;

    void update(std::weak_ptr<GameInterface> gameInstance, float elapsed) override;

    void draw(std::shared_ptr<RenderTarget> rt) override;

    void setTransition(std::shared_ptr<StateManagerTransitionInterface> transition) override;

    std::shared_ptr<StateManagerTransitionInterface> getTransition();

private:
    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };
    std::shared_ptr<StateManagerTransitionInterface> m_transition { nullptr };
    bool m_updatedOnce { false };

    void doSwitchState(std::weak_ptr<GameInterface> gameInstance);
};
} // namespace jt

#endif // GUARD_JAMTEMAPLTE_STATE_MANAGER_HPP
