#ifndef JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "SmartObject.hpp"

namespace JamTemplate {
class SmartShape : public SmartObject {
public:
    using Sptr = std::shared_ptr<SmartShape>;

    void makeRect(sf::Vector2f size)
    {
        m_shape = std::make_shared<sf::RectangleShape>(size);
        m_flashShape = std::make_shared<sf::RectangleShape>(size);
    }
    void makeCircle(float radius, unsigned int points = 30U)
    {
        m_shape = std::make_shared<sf::CircleShape>(radius, points);
        m_flashShape = std::make_shared<sf::CircleShape>(radius, points);
    }

    void setColor(sf::Color const& col) override
    {
        m_shape->setFillColor(col);
    }
    const sf::Color getColor() const override
    {
        return m_shape->getFillColor();
    }

    void setFlashColor(sf::Color const& col) override
    {
        m_flashShape->setFillColor(col);
    }
    const sf::Color getFlashColor() const override
    {
        return m_flashShape->getFillColor();
    }

    void setPosition(sf::Vector2f const& pos) override
    {
        m_position = pos;
    }
    const sf::Vector2f getPosition() const override
    {
        return m_position;
    }

    sf::Transform const getTransform() const override
    {
        return m_shape->getTransform();
    }
    sf::FloatRect getGlobalBounds() const override
    {
        return m_shape->getGlobalBounds();
    }
    virtual sf::FloatRect getLocalBounds() const override
    {
        return m_shape->getLocalBounds();
    }

    std::shared_ptr<sf::Shape> getShape()
    {
        return m_shape;
    }

    void setScale(sf::Vector2f const& scale)
    {
        m_shape->setScale(scale);
    }
    const sf::Vector2f getScale() const
    {
        return m_shape->getScale();
    }

    void setOrigin(sf::Vector2f const& origin)
    {
        m_shape->setOrigin(origin);
        m_flashShape->setOrigin(origin);
    }
    const sf::Vector2f getOrigin() const
    {
        return m_shape->getOrigin();
    }

private:
    std::shared_ptr<sf::Shape> m_shape = nullptr;
    std::shared_ptr<sf::Shape> m_flashShape = nullptr;

    sf::Vector2f m_position { 0, 0 };

    void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const override
    {
        sptr->draw(*m_shape);
    }

    void doDrawFlash(std::shared_ptr<sf::RenderTarget> sptr) const override
    {
        sptr->draw(*m_flashShape);
    }

    void doUpdate(float /*elapsed*/) override
    {
        m_shape->setPosition(getPosition() + getShakeOffset() + getOffset() + getCamOffset());
        m_flashShape->setPosition(getPosition() + getShakeOffset() + getOffset() + getCamOffset());
        m_flashShape->setScale(m_shape->getScale());
    }

    void doRotate(float rot)
    {
        m_shape->setRotation(-rot);
        m_flashShape->setRotation(-rot);
    }
};
} // namespace JamTemplate

#endif
