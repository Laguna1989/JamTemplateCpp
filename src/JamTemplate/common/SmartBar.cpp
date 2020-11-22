#include "SmartBar.hpp"
#include "Game.hpp"

namespace JamTemplate {

SmartBar::SmartBar(float width, float height)
    : m_valueCurrent { 0.0f }
    , m_valueMax { 1.0f }
    , m_width { width }
    , m_height { height }
{
    m_shapeFull = sf::RectangleShape(jt::vector2 { m_width, m_height });
    m_shapeFull.setFillColor(jt::color { 150, 150, 150 });

    m_shapeProgress = sf::RectangleShape(jt::vector2 { m_width, m_height * 0.9f });
    m_shapeProgress.setFillColor(jt::color { 255, 255, 255 });
    m_shapeProgress.setPosition(jt::vector2 { 0, m_height * 0.1f });
}

void SmartBar::setFrontColor(jt::color const& col) { m_shapeProgress.setFillColor(col); }
void SmartBar::setBackColor(jt::color const& col) { m_shapeFull.setFillColor(col); }

void SmartBar::doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const
{
    sptr->draw(m_shapeFull);
    sptr->draw(m_shapeProgress);
}

void SmartBar::doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const { }
void SmartBar::doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const
{
    jt::vector2 const oldPos = m_shapeFull.getPosition();
    jt::color const oldCol = m_shapeFull.getFillColor();

    m_shapeFull.setPosition(oldPos + getShadowOffset());
    m_shapeFull.setFillColor(getShadowColor());
    sptr->draw(m_shapeFull);

    m_shapeFull.setPosition(oldPos);
    m_shapeFull.setFillColor(oldCol);
}

void SmartBar::doUpdate(float /*elapsed*/)
{
    float const value = static_cast<float>(m_valueCurrent) / m_valueMax;
    auto const sacleFullShape = m_shapeFull.getScale();
    m_shapeProgress.setScale(value * sacleFullShape.x, sacleFullShape.y);
}
void SmartBar::doFlash(float /*t*/, jt::color /*col = jt::colors::White*/) { }
void SmartBar::doRotate(float /*rot*/) { }

void SmartBar::setColor(jt::color const& col) { setFrontColor(col); }
const jt::color SmartBar::getColor() const { return m_shapeProgress.getFillColor(); }

void SmartBar::setPosition(jt::vector2 const& pos)
{
    m_shapeFull.setPosition(pos);
    m_shapeProgress.setPosition(pos + jt::vector2 { 0, m_height * 0.1f });
}

const jt::vector2 SmartBar::getPosition() const { return m_shapeFull.getPosition(); }

sf::Transform const SmartBar::getTransform() const { return m_shapeFull.getTransform(); }
sf::FloatRect const SmartBar::getGlobalBounds() const { return m_shapeFull.getGlobalBounds(); }
sf::FloatRect const SmartBar::getLocalBounds() const { return m_shapeFull.getLocalBounds(); }

void SmartBar::setFlashColor(jt::color const& /*col*/)
{
    throw std::logic_error { "flash not supported by SmartBar" };
}
const jt::color SmartBar::getFlashColor() const { return jt::colors::White; }

void SmartBar::setScale(jt::vector2 const& scale)
{
    m_shapeFull.setScale(scale);
    m_shapeProgress.setScale(scale);
}
const jt::vector2 SmartBar::getScale() const { return m_shapeFull.getScale(); }

void SmartBar::setOrigin(jt::vector2 const& origin) { m_shapeFull.setOrigin(origin); }
const jt::vector2 SmartBar::getOrigin() const { return m_shapeFull.getOrigin(); }

} // namespace JamTemplate
