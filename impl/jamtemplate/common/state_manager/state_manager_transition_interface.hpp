#ifndef GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP

#include "render_target.hpp"
#include <memory>

namespace jt {
class StateManagerTransitionInterface {
public:
    virtual ~StateManagerTransitionInterface() = default;

    virtual void start() = 0;
    virtual bool isInProgress() = 0;
    virtual bool triggerStateChange() = 0;
    virtual void update(float elapsed) = 0;
    virtual void draw(std::shared_ptr<RenderTarget> rt) = 0;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_INTERFACE_HPP
