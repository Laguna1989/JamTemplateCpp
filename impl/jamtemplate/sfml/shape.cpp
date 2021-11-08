#include "shape.hpp"
#include <SFML/Graphics.hpp>

namespace jt {

void Shape::makeRect(jt::Vector2 size)
{
    m_shape = std::make_shared<sf::RectangleShape>(size);
    m_flashShape = std::make_shared<sf::RectangleShape>(size);
}

void Shape::setColor(jt::Color const& col) { m_shape->setFillColor(col); }
jt::Color Shape::getColor() const { return m_shape->getFillColor(); }

void Shape::setFlashColor(jt::Color const& col) { m_flashShape->setFillColor(col); }
jt::Color Shape::getFlashColor() const { return m_flashShape->getFillColor(); }

void Shape::setPosition(jt::Vector2 const& pos) { m_position = pos; }
jt::Vector2 Shape::getPosition() const { return m_position; }

jt::Rect Shape::getGlobalBounds() const
{
    if (!m_shape) {
        return jt::Rect { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return m_shape->getGlobalBounds();
}
jt::Rect Shape::getLocalBounds() const
{
    if (!m_shape) {
        return jt::Rect { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return m_shape->getLocalBounds();
}

void Shape::setScale(jt::Vector2 const& scale)
{
    if (m_shape) {
        m_shape->setScale(scale);
    }
}

jt::Vector2 Shape::getScale() const
{
    if (!m_shape) {
        return jt::Vector2 { 1.0f, 1.0f };
    }
    return m_shape->getScale();
}

void Shape::setOrigin(jt::Vector2 const& origin)
{
    if (m_shape) {
        m_shape->setOrigin(origin);
        m_flashShape->setOrigin(origin);
    }
}
jt::Vector2 Shape::getOrigin() const
{
    if (!m_shape) {
        return jt::Vector2 { 0.0f, 0.0f };
    }
    return m_shape->getOrigin();
}

void Shape::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (sptr) {
        sptr->draw(*m_shape);
    }
}

void Shape::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (sptr) {
        sptr->draw(*m_flashShape);
    }
}

void Shape::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (sptr) {
        jt::Vector2 const oldPos = m_shape->getPosition();
        jt::Color const oldCol = m_shape->getFillColor();

        m_shape->setPosition(oldPos + getShadowOffset());
        m_shape->setFillColor(getShadowColor());
        sptr->draw(*m_shape);

        m_shape->setPosition(oldPos);
        m_shape->setFillColor(oldCol);
    }
}

void Shape::doUpdate(float /*elapsed*/)
{
    if (m_shape) {
        auto const pos = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
        m_shape->setPosition(pos);
        m_flashShape->setPosition(pos);
        m_flashShape->setScale(m_shape->getScale());
    }
}

void Shape::doRotate(float rot)
{
    if (m_shape) {
        m_shape->setRotation(-rot);
        m_flashShape->setRotation(-rot);
    }
}

} // namespace jt
