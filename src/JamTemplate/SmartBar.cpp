#include "SmartBar.hpp"
#include "Game.hpp"

namespace JamTemplate {

SmartBar::SmartBar(float width, float height)
    : m_valueCurrent { 0.0f }
    , m_valueMax { 1.0f }
    , m_width { width }
    , m_height { height }
{
    m_shapeFull = sf::RectangleShape(sf::Vector2f { m_width, m_height });
    m_shapeFull.setFillColor(sf::Color { 150, 150, 150 });

    m_shapeProgress = sf::RectangleShape(sf::Vector2f { m_width, m_height * 0.9f });
    m_shapeProgress.setFillColor(sf::Color { 255, 255, 255 });
    m_shapeProgress.setPosition(sf::Vector2f { 0, m_height * 0.1f });
}

void SmartBar::setFrontColor(sf::Color const& col) { m_shapeProgress.setFillColor(col); }
void SmartBar::setBackColor(sf::Color const& col) { m_shapeFull.setFillColor(col); }

void SmartBar::doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const
{
    sptr->draw(m_shapeFull);
    sptr->draw(m_shapeProgress);
}

void SmartBar::doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const { }
void SmartBar::doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const
{
    sf::Vector2f const oldPos = m_shapeFull.getPosition();
    sf::Color const oldCol = m_shapeFull.getFillColor();

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
void SmartBar::doFlash(float /*t*/, sf::Color /*col = sf::Color::White*/) { }
void SmartBar::doRotate(float /*rot*/) { }

void SmartBar::setColor(sf::Color const& col) { setFrontColor(col); }
const sf::Color SmartBar::getColor() const { return m_shapeProgress.getFillColor(); }

void SmartBar::setPosition(sf::Vector2f const& pos)
{
    m_shapeFull.setPosition(pos);
    m_shapeProgress.setPosition(pos + sf::Vector2f { 0, m_height * 0.1f });
}

const sf::Vector2f SmartBar::getPosition() const { return m_shapeFull.getPosition(); }

sf::Transform const SmartBar::getTransform() const { return m_shapeFull.getTransform(); }
sf::FloatRect const SmartBar::getGlobalBounds() const { return m_shapeFull.getGlobalBounds(); }
sf::FloatRect const SmartBar::getLocalBounds() const { return m_shapeFull.getLocalBounds(); }

void SmartBar::setFlashColor(sf::Color const& /*col*/)
{
    throw std::logic_error { "flash not supported by SmartBar" };
}
const sf::Color SmartBar::getFlashColor() const { return sf::Color::White; }

void SmartBar::setScale(sf::Vector2f const& scale)
{
    m_shapeFull.setScale(scale);
    m_shapeProgress.setScale(scale);
}
const sf::Vector2f SmartBar::getScale() const { return m_shapeFull.getScale(); }

void SmartBar::setOrigin(sf::Vector2f const& origin) { m_shapeFull.setOrigin(origin); }
const sf::Vector2f SmartBar::getOrigin() const { return m_shapeFull.getOrigin(); }

} // namespace JamTemplate
