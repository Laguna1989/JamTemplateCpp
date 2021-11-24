#ifndef MYAWESOMEGAME_STATE_MANAGER_HPP
#define MYAWESOMEGAME_STATE_MANAGER_HPP

#include "game_state.hpp"
#include <memory>

namespace jt {

class GameInterface;

class StateManager {
public:
    StateManager(std::shared_ptr<GameState> initialState);
    std::shared_ptr<GameState> getCurrentState();

    void switchState(std::shared_ptr<GameState> newState);
    void doSwitchState(std::weak_ptr<GameInterface> gameInstace);

    bool checkForGameStateSwitch(std::weak_ptr<GameInterface> gameInstace);

    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };

private:
};
} // namespace jt

#endif // MYAWESOMEGAME_STATE_MANAGER_HPP
