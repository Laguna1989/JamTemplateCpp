#include "shape.hpp"
#include "color_lib.hpp"
#include "rect_lib.hpp"
#include "vector_lib.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void jt::Shape::makeRect(jt::Vector2f size, jt::TextureManagerInterface& /*unused*/)
{
    m_shape = std::make_shared<sf::RectangleShape>(toLib(size));
    m_flashShape = std::make_shared<sf::RectangleShape>(toLib(size));
}

void jt::Shape::makeCircle(float radius, jt::TextureManagerInterface& /*unused*/)
{
    m_shape = std::make_shared<sf::CircleShape>(radius);
    m_flashShape = std::make_shared<sf::CircleShape>(radius);
}

void jt::Shape::setColor(jt::Color const& col) { m_shape->setFillColor(toLib(col)); }
jt::Color jt::Shape::getColor() const { return fromLib(m_shape->getFillColor()); }

void jt::Shape::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f jt::Shape::getPosition() const { return m_position; }

jt::Rectf jt::Shape::getGlobalBounds() const
{
    if (!m_shape) {
        return jt::Rectf { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return fromLib(m_shape->getGlobalBounds());
}
jt::Rectf jt::Shape::getLocalBounds() const
{
    if (!m_shape) {
        return jt::Rectf { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return fromLib(m_shape->getLocalBounds());
}

void jt::Shape::setScale(jt::Vector2f const& scale)
{
    if (m_shape) {
        m_shape->setScale(scale.x, scale.y);
        m_flashShape->setScale(scale.x, scale.y);
    }
}

jt::Vector2f jt::Shape::getScale() const
{
    if (!m_shape) {
        return jt::Vector2f { 1.0f, 1.0f };
    }
    return fromLib(m_shape->getScale());
}

void jt::Shape::setOriginInternal(jt::Vector2f const& origin)
{
    if (m_shape) {
        m_shape->setOrigin(origin.x, origin.y);
        m_flashShape->setOrigin(origin.x, origin.y);
    }
}

void jt::Shape::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    sf::RenderStates states { getSfBlendMode() };
    sptr->draw(*m_shape, states);
}

void jt::Shape::doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (sptr) {
        sptr->draw(*m_flashShape);
    }
}

void jt::Shape::doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
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

void jt::Shape::doUpdate(float /*elapsed*/)
{
    if (m_shape) {
        auto const screenPosition
            = getPosition() + getShakeOffset() + getOffset() + getCompleteCamOffset();
        m_shape->setPosition(screenPosition.x, screenPosition.y);
        m_flashShape->setPosition(screenPosition.x, screenPosition.y);
        m_flashShape->setFillColor(toLib(getFlashColor()));
    }
}

void jt::Shape::doRotate(float rot)
{
    if (m_shape) {
        m_shape->setRotation(-rot);
        m_flashShape->setRotation(-rot);
    }
}
