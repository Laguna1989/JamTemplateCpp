#ifndef JAMTEMPLATE_STATE_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_STATE_MANAGER_INTERFACE_HPP

#include <game_state.hpp>
#include <state_manager/state_manager_transition_interface.hpp>

namespace jt {

class GameInterface;

class StateManagerInterface {
public:
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

    /// Switch to a stored state.
    ///
    /// Note: An Exception will be raised if there is no state with the identifier.
    /// \param identifier identifier of the state to switch to
    virtual void switchToStoredState(std::string const& identifier) = 0;

    /// Store the current GameState with the given identifier
    /// \param identifier identifier for the current state
    virtual void storeCurrentState(std::string const& identifier) = 0;

    /// Retrieve a stored GameState
    /// \param identifier the identifier to look for
    /// \return shared pointer to a stored GameState. If no state was stored, a nullptr is returned.
    virtual std::shared_ptr<jt::GameState> getStoredState(std::string const& identifier) = 0;

    /// Clear a stored GameState
    /// \param identifier the identifier to clear
    virtual void clearStoredState(std::string const& identifier) = 0;

    /// Get the Identifiers of the stored states
    /// \return a vector of stored State Identifiers.
    virtual std::vector<std::string> getStoredStateIdentifiers() const = 0;

    /// Check for pending Game State Switch
    /// \param gameInstance instance of the game
    /// \return true if switch was performed, false otherwise
    virtual void update(std::weak_ptr<GameInterface> gameInstance, float elapsed) = 0;

    /// Draw the state
    /// \param rt
    virtual void draw(std::shared_ptr<jt::RenderTargetInterface> rt) = 0;

    /// Destructor
    virtual ~StateManagerInterface() = default;

    // no copy, no move. Avoid slicing.
    StateManagerInterface(StateManagerInterface const&) = delete;
    StateManagerInterface(StateManagerInterface&&) = delete;
    StateManagerInterface& operator=(StateManagerInterface const&) = delete;
    StateManagerInterface& operator=(StateManagerInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    StateManagerInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_STATE_MANAGER_INTERFACE_HPP
