#include "SmartShape.hpp"

namespace jt {

void SmartShape::makeRect(jt::Vector2 size)
{
    m_shape = std::make_shared<sf::RectangleShape>(size);
    m_flashShape = std::make_shared<sf::RectangleShape>(size);
}

void SmartShape::setColor(jt::Color const& col) { m_shape->setFillColor(col); }
const jt::Color SmartShape::getColor() const { return m_shape->getFillColor(); }

void SmartShape::setFlashColor(jt::Color const& col) { m_flashShape->setFillColor(col); }
const jt::Color SmartShape::getFlashColor() const { return m_flashShape->getFillColor(); }

void SmartShape::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 SmartShape::getPosition() const { return m_position; }

// sf::Transform const getTransform() const  { return m_shape->getTransform(); }
jt::Rect const SmartShape::getGlobalBounds() const { return m_shape->getGlobalBounds(); }
jt::Rect const SmartShape::getLocalBounds() const { return m_shape->getLocalBounds(); }

std::shared_ptr<sf::Shape> SmartShape::getShape() { return m_shape; }

void SmartShape::setScale(jt::Vector2 const& scale) { m_shape->setScale(scale); }
const jt::Vector2 SmartShape::getScale() const { return m_shape->getScale(); }

void SmartShape::setOrigin(jt::Vector2 const& origin)
{
    m_shape->setOrigin(origin);
    m_flashShape->setOrigin(origin);
}
const jt::Vector2 SmartShape::getOrigin() const { return m_shape->getOrigin(); }

void SmartShape::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    sptr->draw(*m_shape);
}

void SmartShape::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    sptr->draw(*m_flashShape);
}

void SmartShape::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    jt::Vector2 const oldPos = m_shape->getPosition();
    jt::Color const oldCol = m_shape->getFillColor();

    m_shape->setPosition(oldPos + getShadowOffset());
    m_shape->setFillColor(getShadowColor());
    sptr->draw(*m_shape);

    m_shape->setPosition(oldPos);
    m_shape->setFillColor(oldCol);
}

void SmartShape::doUpdate(float /*elapsed*/)
{
    auto const pos = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
    m_shape->setPosition(pos);
    m_flashShape->setPosition(pos);
    m_flashShape->setScale(m_shape->getScale());
}

void SmartShape::doRotate(float rot)
{
    m_shape->setRotation(-rot);
    m_flashShape->setRotation(-rot);
}

} // namespace jt
