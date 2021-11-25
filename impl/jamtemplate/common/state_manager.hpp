#ifndef MYAWESOMEGAME_STATE_MANAGER_HPP
#define MYAWESOMEGAME_STATE_MANAGER_HPP

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

    bool checkForGameStateSwitch(std::weak_ptr<GameInterface> gameInstance) override;

private:
    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };

    void doSwitchState(std::weak_ptr<GameInterface> gameInstace);
};
} // namespace jt

#endif // MYAWESOMEGAME_STATE_MANAGER_HPP
