#ifndef GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_IMPL_HPP
#define GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_IMPL_HPP

#include "state_manager_interface.hpp"

namespace jt {

class StateManagerTransitionImpl : public StateManagerTransitionInterface {
public:
    StateManagerTransitionImpl(float timerMax);

    virtual ~StateManagerTransitionImpl() = default;

    void start() override;
    bool isInProgress() override;
    bool triggerStateChange() override;
    void update(float elapsed) override;
    void draw(std::shared_ptr<RenderTarget> rt) override;

    float getRatio() const;
    bool isInFirstHalf() const;

private:
    bool m_started { false };
    float m_timer { 0.0f };
    float m_timerMax { 1.0f };
    bool m_isInProgress { false };
    bool m_triggerStateChange { false };
    bool m_firstHalf { true };

    virtual void doUpdate(float elapsed) = 0;
    virtual void doStart() = 0;
    virtual void doDraw(std::shared_ptr<jt::RenderTarget> rt) = 0;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_IMPL_HPP
