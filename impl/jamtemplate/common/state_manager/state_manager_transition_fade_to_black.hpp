#ifndef GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_FADE_TO_BLACK_HPP
#define GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_FADE_TO_BLACK_HPP

#include "shape.hpp"
#include "state_manager_transition_interface.hpp"
#include "vector.hpp"

namespace jt {

class StateManagerTransitionFadeToBlack : public StateManagerTransitionInterface {
public:
    StateManagerTransitionFadeToBlack(
        jt::Vector2f const& size, TextureManagerInterface& tm, float timerMax = 0.5f);
    bool isInProgress() override;
    void update(float elapsed) override;
    void draw(std::shared_ptr<RenderTarget> rt) override;
    void reset() override;
    bool triggerStateChange() override;
    void start() override;

private:
    std::shared_ptr<jt::Shape> m_shape { nullptr };
    bool m_started { false };
    float m_timer { 0.0f };
    float m_timerMax { 1.0f };
    bool m_isInProgress { false };
    bool m_triggerStateChange { false };
    bool m_firstHalf { true };
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_FADE_TO_BLACK_HPP
