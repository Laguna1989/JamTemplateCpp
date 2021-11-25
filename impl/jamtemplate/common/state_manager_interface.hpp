#ifndef MYAWESOMEGAME_STATE_MANAGER_INTERFACE_HPP
#define MYAWESOMEGAME_STATE_MANAGER_INTERFACE_HPP

#include "game_state.hpp"

namespace jt {

class GameInterface;

class StateManagerInterface {
public:
    /// Destructor
    virtual ~StateManagerInterface() = default;

    /// Get the current GameState
    /// \return the current state
    virtual std::shared_ptr<GameState> getCurrentState() = 0;

    /// Switch to a new state
    ///
    /// The actual switch might be delayed and happen at a later time.
    /// \param newState the new state
    virtual void switchState(std::shared_ptr<GameState> newState) = 0;

    /// Check for pending Game State Switch
    /// \param gameInstance instance of the game
    /// \return true if switch was performed, false otherwise
    virtual bool checkForGameStateSwitch(std::weak_ptr<GameInterface> gameInstance) = 0;
};

} // namespace jt

#endif // MYAWESOMEGAME_STATE_MANAGER_INTERFACE_HPP
