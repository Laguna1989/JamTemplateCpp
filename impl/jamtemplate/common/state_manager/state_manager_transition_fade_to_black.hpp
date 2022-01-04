#ifndef GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_FADE_TO_BLACK_HPP
#define GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_FADE_TO_BLACK_HPP

#include "shape.hpp"
#include "state_manager_transition_impl.hpp"
#include "vector.hpp"

namespace jt {

class StateManagerTransitionFadeToBlack : public StateManagerTransitionImpl {
public:
    StateManagerTransitionFadeToBlack(
        jt::Vector2f const& overlaySize, TextureManagerInterface& tm, float timerMax = 0.5f);

private:
    std::shared_ptr<jt::Shape> m_shape { nullptr };

    void doUpdate(float elapsed) override;
    void doStart() override;
    void doDraw(std::shared_ptr<jt::RenderTarget> rt) override;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_STATE_MANAGER_TRANSITION_FADE_TO_BLACK_HPP
