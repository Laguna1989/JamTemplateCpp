#include "shape.hpp"
#include <color_lib.hpp>
#include <math_helper.hpp>
#include <rect_lib.hpp>
#include <vector_lib.hpp>

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
    if (!m_shape) [[unlikely]] {
        return jt::Rectf { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return fromLib(m_shape->getGlobalBounds());
}

jt::Rectf jt::Shape::getLocalBounds() const
{
    if (!m_shape) [[unlikely]] {
        return jt::Rectf { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return fromLib(m_shape->getLocalBounds());
}

void jt::Shape::setScale(jt::Vector2f const& scale)
{
    if (m_shape) [[likely]] {
        m_shape->setScale(scale.x, scale.y);
        m_flashShape->setScale(scale.x, scale.y);
    }
}

jt::Vector2f jt::Shape::getScale() const
{
    if (!m_shape) [[unlikely]] {
        return jt::Vector2f { 1.0f, 1.0f };
    }
    return fromLib(m_shape->getScale());
}

void jt::Shape::setOriginInternal(jt::Vector2f const& origin)
{
    if (m_shape) [[likely]] {
        m_shape->setOrigin(origin.x, origin.y);
        m_flashShape->setOrigin(origin.x, origin.y);
    }
}

void jt::Shape::doUpdate(float /*elapsed*/)
{
    if (!m_shape) [[unlikely]] {
        return;
    }

    auto const floatPos = getPosition() + getShakeOffset() + getOffset() + getCompleteCamOffset();

    auto const screenPosition = jt::MathHelper::castToInteger(floatPos);
    m_shape->setPosition(screenPosition.x, screenPosition.y);
    m_flashShape->setPosition(screenPosition.x, screenPosition.y);
    m_flashShape->setFillColor(toLib(getFlashColor()));
}

void jt::Shape::doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!m_shape) [[unlikely]] {
        return;
    }
    if (!sptr) [[unlikely]] {
        return;
    }

    jt::Vector2f const oldPos = fromLib(m_shape->getPosition());
    auto const oldCol = fromLib(m_shape->getFillColor());

    m_shape->setPosition(toLib(jt::MathHelper::castToInteger(oldPos + getShadowOffset())));
    m_shape->setFillColor(toLib(getShadowColor()));
    sptr->draw(*m_shape);

    m_shape->setPosition(toLib(oldPos));
    m_shape->setFillColor(toLib(oldCol));
}

void jt::Shape::doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!m_shape) [[unlikely]] {
        return;
    }
    if (!sptr) [[unlikely]] {
        return;
    }

    jt::Vector2f const oldPos = fromLib(m_shape->getPosition());
    jt::Color const oldCol = fromLib(m_shape->getFillColor());

    m_shape->setFillColor(toLib(getOutlineColor()));

    for (auto const outlineOffset : getOutlineOffsets()) {
        m_shape->setPosition(toLib(jt::MathHelper::castToInteger(oldPos + outlineOffset)));
        sptr->draw(*m_shape);
    }

    m_shape->setPosition(toLib(oldPos));
    m_shape->setFillColor(toLib(oldCol));
}

void jt::Shape::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!m_shape) [[unlikely]] {
        return;
    }
    if (!sptr) [[unlikely]] {
        return;
    }

    sf::RenderStates const states { getSfBlendMode() };
    sptr->draw(*m_shape, states);
}

void jt::Shape::doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!m_shape) [[unlikely]] {
        return;
    }
    if (!sptr) [[unlikely]] {
        return;
    }

    sptr->draw(*m_flashShape);
}

void jt::Shape::doRotate(float rot)
{
    if (!m_shape) [[unlikely]] {
        return;
    }

    m_shape->setRotation(rot);
    m_flashShape->setRotation(rot);
}
