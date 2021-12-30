#ifndef GUARD_JAMTEMPLATE_DRAWABLEINTERFACE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_DRAWABLEINTERFACE_HPP_INCLUDEGUARD

#include "color.hpp"
#include "rect.hpp"
#include "render_target.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {
class DrawableInterface {
public:
    using Sptr = std::shared_ptr<DrawableInterface>;

    /// Destructor
    virtual ~DrawableInterface() = default;

    /// Draw the drawable on the passed render target
    /// \param renderTarget shared pointer to the rendertarget the drawable should be drawn on
    virtual void draw(std::shared_ptr<jt::RenderTarget> renderTarget) const = 0;

    /// Flash the drawable
    /// \param timeInSeconds duration of the flash
    /// \param col color of the flash
    virtual void flash(float timeInSeconds, jt::Color col = jt::colors::White) = 0;

    /// Shake the drawable
    /// \param timeInSeconds how long the shake will last
    /// \param maxShakeOffsetInPixel how strong the shake will be
    /// \param shakeInterval how often a new shake offset will be selected
    virtual void shake(
        float timeInSeconds, float maxShakeOffsetInPixel, float shakeInterval = 0.05f)
        = 0;

    /// update the drawable
    /// \param elapsed the time elapsed (in seconds)
    virtual void update(float elapsed) = 0;

    /// Set the color of the drawable
    /// \param col the new color
    virtual void setColor(jt::Color const& col) = 0;

    /// Get the color of the drawable
    /// \return the color
    virtual jt::Color getColor() const = 0;

    /// Set the position of the drawable
    /// \param pos the new position
    virtual void setPosition(jt::Vector2f const& pos) = 0;

    /// Get the position of the drawable
    /// \return the position
    virtual jt::Vector2f getPosition() const = 0;

    /// Get the global bounds rect
    ///
    /// Global bounds rect is defined by the top left corner of the drawable and its witdh and
    /// height
    ///
    /// \return the global bounds rect
    virtual jt::Rectf getGlobalBounds() const = 0;

    /// Get the local bounds rect
    ///
    /// Local bounds rect is defined by 0, 0 and the width and height
    ///
    /// \return the local bounds rect
    virtual jt::Rectf getLocalBounds() const = 0;

    /// Set the flash color of the drawable
    /// \param col the color
    virtual void setFlashColor(jt::Color const& col) = 0;

    /// Get the flash color of the drawable
    /// \return the color
    virtual jt::Color getFlashColor() const = 0;

    /// Set the scale of the drawable
    /// \param scale the scale
    virtual void setScale(jt::Vector2f const& scale) = 0;

    /// Get the scale of the drawalbe
    /// \return the scale
    virtual jt::Vector2f getScale() const = 0;

    /// Set the origin of the drawable
    ///
    /// The origin is used for rotation
    ///
    /// \param origin the origin
    virtual void setOrigin(jt::Vector2f const& origin) = 0;

    /// Get the origin of the drawable
    /// \return the origin
    virtual jt::Vector2f getOrigin() const = 0;

    /// Set the offset of the drawable
    /// \param offset the offset
    virtual void setOffset(jt::Vector2f const offset) = 0;

    /// get the offset of the drawable
    /// \return the offset
    virtual jt::Vector2f getOffset() const = 0;

    /// Set the rotation angle of the drawable (in degree)
    ///
    /// Rotation will happen around the origin
    ///
    /// \param angleInDegree the rotation
    virtual void setRotation(float angleInDegree) = 0;

    /// Get the rotation angle of the drawable (in degree)
    /// \return the rotation angle
    virtual float getRotation() const = 0;

    /// Set the shadow active status of the of the drawable
    /// \param active
    virtual void setShadowActive(bool active) = 0;

    /// Get the shadow active status of the drawable
    /// \return the shadow active status
    virtual bool getShadowActive() const = 0;

    /// Set the shadow color of the drawable
    /// \param col the color
    virtual void setShadowColor(jt::Color const& col) = 0;

    /// Get the shadow color of the drawable
    /// \return the color
    virtual jt::Color getShadowColor() const = 0;

    /// Set the shadow offset
    /// \param shadowOffsetInPixel offset
    virtual void setShadowOffset(jt::Vector2f const& shadowOffsetInPixel) = 0;

    /// Get the shadow offset
    /// \return the offset in pixel
    virtual jt::Vector2f getShadowOffset() const = 0;

    /// Set the shadow
    /// \param shadowColor the shadow color
    /// \param shadowOffset the shadow shadowOffset
    virtual void setShadow(jt::Color const& shadowColor, jt::Vector2f const& shadowOffset) = 0;

    /// Set ignore cam movement for the drawable (e.g. for HUD elements)
    /// \param ignore
    virtual void setIgnoreCamMovement(bool ignore) = 0;

    /// Get ignore cam movement for the drawalbe (e.g. for HUD elements)
    /// \return
    virtual bool getIgnoreCamMovement() const = 0;
};
} // namespace jt

#endif
