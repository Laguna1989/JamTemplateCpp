#ifndef JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP
#define JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP

#include <graphics/render_target_interface.hpp>
#include <memory>

namespace jt {
class StateManagerTransitionInterface {
public:
    virtual ~StateManagerTransitionInterface() = default;

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
};

} // namespace jt

#endif // JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP
