#ifndef JAMTEMPLATE_STATE_MANAGER_TRANSITION_HORIZONTAL_BARS_HPP
#define JAMTEMPLATE_STATE_MANAGER_TRANSITION_HORIZONTAL_BARS_HPP

#include <shape.hpp>
#include <state_manager/state_manager_transition_impl.hpp>
#include <vector.hpp>

namespace jt {

class StateManagerTransitionHorizontalBars : public StateManagerTransitionImpl {
public:
    StateManagerTransitionHorizontalBars(Vector2f const& shapeSize, int numberOfShapes,
        float totalTime, TextureManagerInterface& tm);

private:
    void doUpdate(float elapsed) override;

    void doStart() override;

    void doDraw(std::shared_ptr<jt::RenderTargetInterface> rt) override;

    std::shared_ptr<jt::Shape> m_shape { nullptr };
    int m_numberOfShapes { 0 };
};

} // namespace jt

#endif // JAMTEMPLATE_STATE_MANAGER_TRANSITION_HORIZONTAL_BARS_HPP
