#include "state_manager_transition_fade_to_black.hpp"
#include <math_helper.hpp>
#include <iostream>

jt::StateManagerTransitionFadeToBlack::StateManagerTransitionFadeToBlack(
    jt::Vector2f const& overlaySize, jt::TextureManagerInterface& tm, float timerMax)
    : StateManagerTransitionImpl { timerMax }
    , m_shape { std::make_shared<jt::Shape>() }
{
    m_shape->makeRect(overlaySize, tm);
    m_shape->setColor(jt::Color { 0, 0, 0, 0 });
    m_shape->setIgnoreCamMovement(true);
}

void jt::StateManagerTransitionFadeToBlack::doUpdate(float elapsed)
{
    std::uint8_t a { static_cast<std::uint8_t>(getRatio() * 255.0f) };
    jt::Color const col { 0, 0, 0, a };
    m_shape->setColor(col);
    m_shape->update(elapsed);
}

void jt::StateManagerTransitionFadeToBlack::doStart()
{
    m_shape->setColor(jt::Color { 0, 0, 0, 0 });
}

void jt::StateManagerTransitionFadeToBlack::doDraw(
    std::shared_ptr<jt::RenderTargetInterface> rt)
{
    m_shape->draw(rt);
}
