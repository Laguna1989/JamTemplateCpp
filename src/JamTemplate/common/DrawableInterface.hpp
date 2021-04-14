#ifndef GUARD_JAMTEMPLATE_DRAWABLEINTERFACE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_DRAWABLEINTERFACE_HPP_INCLUDEGUARD

#include "Lerp.hpp"
#include "Random.hpp"
#include "Rendertarget.hpp"
#include "Vector.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace jt {
class DrawableInterface {
public:
    using Sptr = std::shared_ptr<DrawableInterface>;

    virtual void draw(std::shared_ptr<jt::renderTarget> sptr) const = 0;

    virtual void flash(float t, jt::Color col = jt::colors::White) = 0;

    virtual void shake(float t, float strength, float shakeInterval = 0.05f) = 0;

    virtual void update(float elapsed) = 0;

    virtual void setColor(jt::Color const& col) = 0;
    virtual const jt::Color getColor() const = 0;

    virtual void setPosition(jt::Vector2 const& pos) = 0;
    virtual const jt::Vector2 getPosition() const = 0;

    // virtual sf::Transform const getTransform() const = 0;
    virtual jt::Rect const getGlobalBounds() const = 0;
    virtual jt::Rect const getLocalBounds() const = 0;

    virtual void setFlashColor(jt::Color const& col) = 0;
    virtual const jt::Color getFlashColor() const = 0;

    virtual void setScale(jt::Vector2 const& scale) = 0;
    virtual const jt::Vector2 getScale() const = 0;

    virtual void setOrigin(jt::Vector2 const& origin) = 0;
    virtual const jt::Vector2 getOrigin() const = 0;

    virtual jt::Vector2 getOffset() const = 0;
    virtual void setOffset(jt::Vector2 const offset) = 0;

    virtual void setRotation(float rot) = 0;
    virtual float getRotation() const = 0;

    virtual void setShadowActive(bool active) = 0;
    virtual bool getShadowActive() const = 0;
    virtual void setShadowColor(jt::Color const& col) = 0;
    virtual jt::Color const getShadowColor() const = 0;
    virtual void setShadowOffset(jt::Vector2 const& v) = 0;
    virtual jt::Vector2 const getShadowOffset() const = 0;
    virtual void setShadow(jt::Color const& col, jt::Vector2 const& offset) = 0;

    virtual void setIgnoreCamMovement(bool ignore) = 0;
};
} // namespace jt

#endif
