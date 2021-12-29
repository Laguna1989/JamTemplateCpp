#include "shape.hpp"
#include "color_lib.hpp"
#include "rect_lib.hpp"
#include "vector_lib.hpp"
#include <SFML/Graphics.hpp>

namespace jt {

void Shape::makeRect(jt::Vector2f size, TextureManagerInterface& /*unused*/)
{
    m_shape = std::make_shared<sf::RectangleShape>(toLib(size));
    m_flashShape = std::make_shared<sf::RectangleShape>(toLib(size));
}

void Shape::makeCircle(float radius, TextureManagerInterface& /*unused*/)
{
    m_shape = std::make_shared<sf::CircleShape>(radius);
    m_flashShape = std::make_shared<sf::CircleShape>(radius);
}

void Shape::setColor(jt::Color const& col) { m_shape->setFillColor(toLib(col)); }
jt::Color Shape::getColor() const { return fromLib(m_shape->getFillColor()); }

void Shape::setFlashColor(jt::Color const& col) { m_flashShape->setFillColor(toLib(col)); }
jt::Color Shape::getFlashColor() const { return fromLib(m_flashShape->getFillColor()); }

void Shape::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f Shape::getPosition() const { return m_position; }

jt::Rectf Shape::getGlobalBounds() const
{
    if (!m_shape) {
        return jt::Rectf { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return fromLib(m_shape->getGlobalBounds());
}
jt::Rectf Shape::getLocalBounds() const
{
    if (!m_shape) {
        return jt::Rectf { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return fromLib(m_shape->getLocalBounds());
}

void Shape::setScale(jt::Vector2f const& scale)
{
    if (m_shape) {
        m_shape->setScale(toLib(scale));
    }
}

jt::Vector2f Shape::getScale() const
{
    if (!m_shape) {
        return jt::Vector2f { 1.0f, 1.0f };
    }
    return fromLib(m_shape->getScale());
}

void Shape::setOrigin(jt::Vector2f const& origin)
{
    if (m_shape) {
        m_shape->setOrigin(toLib(origin));
        m_flashShape->setOrigin(toLib(origin));
    }
}
jt::Vector2f Shape::getOrigin() const
{
    if (!m_shape) {
        return jt::Vector2f { 0.0f, 0.0f };
    }
    return fromLib(m_shape->getOrigin());
}

void Shape::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (sptr) {
        sptr->draw(*m_shape);
    }
}

void Shape::doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (sptr) {
        sptr->draw(*m_flashShape);
    }
}

void Shape::doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (sptr) {
        jt::Vector2f const oldPos = fromLib(m_shape->getPosition());
        auto const oldCol = fromLib(m_shape->getFillColor());

        m_shape->setPosition(toLib(oldPos + getShadowOffset()));
        m_shape->setFillColor(toLib(getShadowColor()));
        sptr->draw(*m_shape);

        m_shape->setPosition(toLib(oldPos));
        m_shape->setFillColor(toLib(oldCol));
    }
}

void Shape::doUpdate(float /*elapsed*/)
{
    if (m_shape) {
        auto const pos = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
        m_shape->setPosition(toLib(pos));
        m_flashShape->setPosition(toLib(pos));
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
