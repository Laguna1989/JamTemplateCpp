#ifndef JAMTEMPLATE_STATE_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_STATE_MANAGER_INTERFACE_HPP

#include <game_state.hpp>
#include <state_manager/state_manager_transition_interface.hpp>

namespace jt {

class GameInterface;

class StateManagerInterface {
public:
    /// Destructor
    virtual ~StateManagerInterface() = default;

    /// Get the current GameState
    /// \return the current state
    virtual std::shared_ptr<GameState> getCurrentState() = 0;

    /// Set the state switch transition
    /// \param transition the transition to play
    virtual void setTransition(std::shared_ptr<StateManagerTransitionInterface> transition) = 0;

    /// Get the set state switch transition
    /// \return the set transition
    virtual std::shared_ptr<StateManagerTransitionInterface> getTransition() = 0;

    /// Switch to a new state
    ///
    /// The actual switch might be delayed and happen at a later time.
    /// \param newState the new state
    virtual void switchState(std::shared_ptr<GameState> newState) = 0;

    /// Check for pending Game State Switch
    /// \param gameInstance instance of the game
    /// \return true if switch was performed, false otherwise
    virtual void update(std::weak_ptr<GameInterface> gameInstance, float elapsed) = 0;

    /// Draw the state
    /// \param rt
    virtual void draw(std::shared_ptr<jt::RenderTargetInterface> rt) = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_STATE_MANAGER_INTERFACE_HPP
