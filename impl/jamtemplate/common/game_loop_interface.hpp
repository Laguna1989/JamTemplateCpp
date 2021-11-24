#ifndef GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD

#include "game_state.hpp"
#include <type_traits>

namespace jt {

/// Interface for handling game loop related functionality
class GameLoopInterface {
public:
    using GameLoopFunctionPtr = std::add_pointer<void()>::type;

    /// Run the Game
    virtual void run() = 0;
    /// Start the game
    /// \param initialState the initial GameState
    /// \param gameloopFunction the game loop function
    virtual void startGame(GameLoopFunctionPtr gameloopFunction) = 0;
};
} // namespace jt
#endif
