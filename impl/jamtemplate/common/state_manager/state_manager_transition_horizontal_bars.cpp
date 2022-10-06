#include "state_manager_transition_horizontal_bars.hpp"

jt::StateManagerTransitionHorizontalBars::StateManagerTransitionHorizontalBars(
    jt::Vector2f const& shapeSize, int numberOfShapes, float totalTime,
    jt::TextureManagerInterface& tm)
    : StateManagerTransitionImpl { totalTime }
    , m_shape { std::make_shared<jt::Shape>() }
    , m_numberOfShapes { numberOfShapes }
{
    m_shape->makeRect(shapeSize, tm);
    m_shape->setColor(jt::Color { 45, 45, 45, 255 });
    m_shape->setIgnoreCamMovement(true);
}

void jt::StateManagerTransitionHorizontalBars::doUpdate(float /*elapsed*/) { }
void jt::StateManagerTransitionHorizontalBars::doStart() { }
void jt::StateManagerTransitionHorizontalBars::doDraw(
    std::shared_ptr<jt::RenderTargetInterface> rt)
{
    for (auto i = 0; i != m_numberOfShapes; ++i) {

        float const posY = i * m_shape->getLocalBounds().height;

        if (i % 2 == 0) {
            float const posX = (getRatio() - 1) * m_shape->getLocalBounds().width;
            m_shape->setPosition(jt::Vector2f { posX, posY });
        } else {
            float const posX = (1 - getRatio()) * m_shape->getLocalBounds().width;
            m_shape->setPosition(jt::Vector2f { posX, posY });
        }
        m_shape->update(0.01f);
        m_shape->draw(rt);
    }
}
