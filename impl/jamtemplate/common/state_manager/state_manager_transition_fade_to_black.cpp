#include "state_manager_transition_fade_to_black.hpp"
#include "math_helper.hpp"
#include <iostream>

namespace jt {

StateManagerTransitionFadeToBlack::StateManagerTransitionFadeToBlack(
    Vector2f const& overlaySize, TextureManagerInterface& tm, float timerMax)
    : StateManagerTransitionImpl(timerMax)
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(overlaySize, tm);
    m_shape->setColor(jt::Color { 0, 0, 0, 0 });
    m_shape->setIgnoreCamMovement(true);
}

void StateManagerTransitionFadeToBlack::doUpdate(float elapsed)
{
    std::uint8_t a { static_cast<std::uint8_t>(getRatio() * 255.0f) };
    jt::Color const col { 0, 0, 0, a };
    m_shape->setColor(col);
    m_shape->update(elapsed);
}

void StateManagerTransitionFadeToBlack::doStart() { m_shape->setColor(jt::Color { 0, 0, 0, 0 }); }

void StateManagerTransitionFadeToBlack::doDraw(std::shared_ptr<jt::RenderTarget> rt)
{
    m_shape->draw(rt);
}

} // namespace jt
