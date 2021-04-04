#include "Shape.hpp"

namespace jt {

void Shape::makeRect(jt::Vector2 size)
{
    m_shape = std::make_shared<sf::RectangleShape>(size);
    m_flashShape = std::make_shared<sf::RectangleShape>(size);
}

void Shape::setColor(jt::Color const& col) { m_shape->setFillColor(col); }
const jt::Color Shape::getColor() const { return m_shape->getFillColor(); }

void Shape::setFlashColor(jt::Color const& col) { m_flashShape->setFillColor(col); }
const jt::Color Shape::getFlashColor() const { return m_flashShape->getFillColor(); }

void Shape::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 Shape::getPosition() const { return m_position; }

// sf::Transform const getTransform() const  { return m_shape->getTransform(); }
jt::Rect const Shape::getGlobalBounds() const { return m_shape->getGlobalBounds(); }
jt::Rect const Shape::getLocalBounds() const { return m_shape->getLocalBounds(); }

std::shared_ptr<sf::Shape> Shape::getShape() { return m_shape; }

void Shape::setScale(jt::Vector2 const& scale) { m_shape->setScale(scale); }
const jt::Vector2 Shape::getScale() const { return m_shape->getScale(); }

void Shape::setOrigin(jt::Vector2 const& origin)
{
    m_shape->setOrigin(origin);
    m_flashShape->setOrigin(origin);
}
const jt::Vector2 Shape::getOrigin() const { return m_shape->getOrigin(); }

void Shape::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const { sptr->draw(*m_shape); }

void Shape::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    sptr->draw(*m_flashShape);
}

void Shape::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    jt::Vector2 const oldPos = m_shape->getPosition();
    jt::Color const oldCol = m_shape->getFillColor();

    m_shape->setPosition(oldPos + getShadowOffset());
    m_shape->setFillColor(getShadowColor());
    sptr->draw(*m_shape);

    m_shape->setPosition(oldPos);
    m_shape->setFillColor(oldCol);
}

void Shape::doUpdate(float /*elapsed*/)
{
    auto const pos = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
    m_shape->setPosition(pos);
    m_flashShape->setPosition(pos);
    m_flashShape->setScale(m_shape->getScale());
}

void Shape::doRotate(float rot)
{
    m_shape->setRotation(-rot);
    m_flashShape->setRotation(-rot);
}

} // namespace jt
