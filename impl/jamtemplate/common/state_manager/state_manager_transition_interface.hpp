#ifndef JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP
#define JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP

#include <graphics/render_target_interface.hpp>
#include <memory>

namespace jt {
class StateManagerTransitionInterface {
public:
    /// Start a transition
    virtual void start() = 0;

    /// Check if a transition is in progress.
    /// \return true if transition is in progress, false otherwise.
    virtual bool isInProgress() = 0;

    /// Check if the state change should be performed now
    /// \return true if state change should happen
    virtual bool triggerStateChange() = 0;

    /// Update the transition
    /// \param elapsed the elapsed time in seconds
    virtual void update(float elapsed) = 0;

    /// Draw the transition
    /// \param rt the render target
    virtual void draw(std::shared_ptr<jt::RenderTargetInterface> rt) = 0;

    /// Destructor
    virtual ~StateManagerTransitionInterface() = default;

    // no copy, no move. Avoid slicing.
    StateManagerTransitionInterface(StateManagerTransitionInterface const&) = delete;
    StateManagerTransitionInterface(StateManagerTransitionInterface&&) = delete;
    StateManagerTransitionInterface& operator=(StateManagerTransitionInterface const&) = delete;
    StateManagerTransitionInterface& operator=(StateManagerTransitionInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    StateManagerTransitionInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP
