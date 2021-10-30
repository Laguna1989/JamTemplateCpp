#ifndef GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD

#include "game_state.hpp"
#include <type_traits>

namespace jt {

/// Interface for handling game loop related functionality
class GameLoopInterface {
public:
    using GameLoopFunctionPtr = std::add_pointer<void()>::type;

    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    /// Switch Gamestate
    ///
    /// Will only switch after the next call to update
    ///
    /// \param newState the new state to be switched to
    virtual void switchState(std::shared_ptr<GameState> newState) = 0;

    /// Get the current GameState
    /// \return the game state
    virtual std::shared_ptr<GameState> getCurrentState() = 0;

    /// Run the Game
    virtual void run() = 0;
    /// Start the game
    /// \param initialState the initial GameState
    /// \param gameloopFunction the game loop function
    virtual void startGame(
        std::shared_ptr<GameState> initialState, GameLoopFunctionPtr gameloopFunction)
        = 0;
};
} // namespace jt
#endif
