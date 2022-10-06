#ifndef JAMTEMPLATE_STATE_MANAGER_TRANSITION_NONE_HPP
#define JAMTEMPLATE_STATE_MANAGER_TRANSITION_NONE_HPP

#include <state_manager/state_manager_transition_interface.hpp>

namespace jt {

class StateManagerTransitionNone : public StateManagerTransitionInterface {
public:
    void start() override;
    bool isInProgress() override;
    void update(float elapsed) override;
    void draw(std::shared_ptr<jt::RenderTargetInterface> rt) override;
    bool triggerStateChange() override;

private:
    bool m_triggerdStateChange { false };
};

} // namespace jt

#endif // JAMTEMPLATE_STATE_MANAGER_TRANSITION_NONE_HPP
