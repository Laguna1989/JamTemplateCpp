#ifndef GUARD_JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "rendertarget.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace jt {
class SmartShape : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartShape>;

    void makeRect(jt::Vector2 size)
    {
        m_shape = std::make_shared<sf::RectangleShape>(size);
        m_flashShape = std::make_shared<sf::RectangleShape>(size);
    }

    void setColor(jt::Color const& col) override { m_shape->setFillColor(col); }
    const jt::Color getColor() const override { return m_shape->getFillColor(); }

    void setFlashColor(jt::Color const& col) override { m_flashShape->setFillColor(col); }
    const jt::Color getFlashColor() const override { return m_flashShape->getFillColor(); }

    void setPosition(jt::Vector2 const& pos) override { m_position = pos; }
    const jt::Vector2 getPosition() const override { return m_position; }

    // sf::Transform const getTransform() const override { return m_shape->getTransform(); }
    jt::Rect const getGlobalBounds() const override { return m_shape->getGlobalBounds(); }
    jt::Rect const getLocalBounds() const override { return m_shape->getLocalBounds(); }

    std::shared_ptr<sf::Shape> getShape() { return m_shape; }

    void setScale(jt::Vector2 const& scale) override { m_shape->setScale(scale); }
    const jt::Vector2 getScale() const override { return m_shape->getScale(); }

    void setOrigin(jt::Vector2 const& origin) override
    {
        m_shape->setOrigin(origin);
        m_flashShape->setOrigin(origin);
    }
    const jt::Vector2 getOrigin() const override { return m_shape->getOrigin(); }

private:
    mutable std::shared_ptr<sf::Shape> m_shape = nullptr;
    std::shared_ptr<sf::Shape> m_flashShape = nullptr;

    jt::Vector2 m_position { 0, 0 };

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        sptr->draw(*m_shape);
    }

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        sptr->draw(*m_flashShape);
    }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        jt::Vector2 const oldPos = m_shape->getPosition();
        jt::Color const oldCol = m_shape->getFillColor();

        m_shape->setPosition(oldPos + getShadowOffset());
        m_shape->setFillColor(getShadowColor());
        sptr->draw(*m_shape);

        m_shape->setPosition(oldPos);
        m_shape->setFillColor(oldCol);
    }

    void doUpdate(float /*elapsed*/) override
    {
        auto const pos = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
        m_shape->setPosition(pos);
        m_flashShape->setPosition(pos);
        m_flashShape->setScale(m_shape->getScale());
    }

    void doRotate(float rot)
    {
        m_shape->setRotation(-rot);
        m_flashShape->setRotation(-rot);
    }
};
} // namespace jt

#endif
