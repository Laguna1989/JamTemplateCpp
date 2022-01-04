
#include "state_manager_transition_horizontal_bars.hpp"

namespace jt {

StateManagerTransitionHorizontalBars::StateManagerTransitionHorizontalBars(
    Vector2f const& shapeSize, int numberOfShapes, float totalTime, TextureManagerInterface& tm)
    : StateManagerTransitionImpl { totalTime }
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(shapeSize, tm);
    m_shape->setColor(jt::Color { 45, 45, 45, 255 });
    m_shape->setIgnoreCamMovement(true);
    m_numberOfShapes = numberOfShapes;
}

void StateManagerTransitionHorizontalBars::doUpdate(float elapsed) { }
void StateManagerTransitionHorizontalBars::doStart() { }
void StateManagerTransitionHorizontalBars::doDraw(std::shared_ptr<jt::RenderTarget> rt)
{
    float const r = getRatio();

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

} // namespace jt
