#ifndef GUARD_JAMTEMAPLTE_STATE_MANAGER_INTERFACE_HPP
#define GUARD_JAMTEMAPLTE_STATE_MANAGER_INTERFACE_HPP

#include "game_state.hpp"
#include "state_manager_transition_interface.hpp"

namespace jt {

class GameInterface;

class StateManagerInterface {
public:
    /// Destructor
    virtual ~StateManagerInterface() = default;

    /// Get the current GameState
    /// \return the current state
    virtual std::shared_ptr<GameState> getCurrentState() = 0;

    /// Set the out transition
    /// \param transition the out transition to play
    virtual void setTransition(std::shared_ptr<StateManagerTransitionInterface> transition) = 0;

    /// Switch to a new state
    ///
    /// The actual switch might be delayed and happen at a later time.
    /// \param newState the new state
    virtual void switchState(std::shared_ptr<GameState> newState) = 0;

    /// Check for pending Game State Switch
    /// \param gameInstance instance of the game
    /// \return true if switch was performed, false otherwise
    virtual void update(std::weak_ptr<GameInterface> gameInstance, float elapsed) = 0;

    virtual void draw(std::shared_ptr<RenderTarget> rt) = 0;
};

} // namespace jt

#endif // GUARD_JAMTEMAPLTE_STATE_MANAGER_INTERFACE_HPP
