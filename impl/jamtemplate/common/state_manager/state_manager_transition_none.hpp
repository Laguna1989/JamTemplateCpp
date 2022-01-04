#ifndef GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_NONE_HPP
#define GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_NONE_HPP

#include "state_manager_transition_interface.hpp"

namespace jt {

class StateManagerTransitionNone : public StateManagerTransitionInterface {
public:
    void start() override;
    bool isInProgress() override;
    void update(float elapsed) override;
    void draw(std::shared_ptr<RenderTarget> rt) override;
    bool triggerStateChange() override;

private:
    bool m_triggerdStateChange { false };
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_NONE_HPP
