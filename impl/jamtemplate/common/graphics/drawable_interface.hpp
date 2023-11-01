#ifndef JAMTEMPLATE_DRAWABLEINTERFACE_HPP
#define JAMTEMPLATE_DRAWABLEINTERFACE_HPP

#include <color/color.hpp>
#include <graphics/render_target_interface.hpp>
#include <rect.hpp>
#include <vector.hpp>
#include <memory>

namespace jt {

enum class BlendMode { ADD, MUL, ALPHA };

enum class OffsetMode { MANUAL, TOPLEFT, CENTER };
enum class OriginMode { MANUAL, TOPLEFT, CENTER };

class DrawableInterface {
public:
    using Sptr = std::shared_ptr<DrawableInterface>;

    /// Draw the drawable on the passed render target
    /// \param renderTarget shared pointer to the rendertarget the drawable should be drawn on
    virtual void draw(std::shared_ptr<jt::RenderTargetInterface> renderTarget) const = 0;

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

    /// Flicker the drawable (toggle drawing on/off)
    /// \param duration how long the flicker will take
    /// \param interval how fast the flicker will switch
    /// \param affectShadow if the shadow is also affected by the flicker effect
    virtual void flicker(float duration, float interval = 0.05f) = 0;

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

    /// Get the position of the drawable in world coordinates
    /// \return the position
    virtual jt::Vector2f getPosition() const = 0;

    /// Get the position of the drawables in screen coordinates.
    /// \return the position on screen
    virtual jt::Vector2f getScreenPosition() const = 0;

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

    /// Set the origin of the drawable
    ///
    /// The origin used for rotation
    ///
    /// \param origin the origin mode
    virtual void setOrigin(jt::OriginMode origin) = 0;

    /// Get the originMode
    ///
    /// The originMode is used for rotation
    ///
    /// \return the originMode
    virtual jt::OriginMode getOriginMode() const = 0;

    /// Set the offset of the drawable
    /// \param offset the offset as a vector
    virtual void setOffset(jt::Vector2f const& offset) = 0;

    /// Get the offsetMode
    /// \return the offsetMode
    virtual jt::OffsetMode getOffsetMode() const = 0;

    /// Set the offset of the drawable
    /// \param offset the offset mode
    virtual void setOffset(jt::OffsetMode offset) = 0;

    /// get the offset of the drawable
    /// \return the offset
    virtual jt::Vector2f getOffset() const = 0;

    /// Set the rotation angle of the drawable (in degree).
    /// Rotation is done counter-clockwise.
    ///
    /// Rotation will happen around the origin.
    ///
    /// \param angleInDegree the rotation
    virtual void setRotation(float angleInDegree) = 0;

    /// Get the rotation angle of the drawable (in degree).
    /// Rotation is done counter-clockwise.
    /// \return the rotation angle
    virtual float getRotation() const = 0;

    /// Set the outline width of the drawable
    /// \param width outline width in pixel
    virtual void setOutline(jt::Color const& col, int width) = 0;

    /// Set the shadow active status of the of the drawable
    /// \param active
    virtual void setShadowActive(bool active) = 0;

    /// Get the shadow active status of the drawable
    /// \return the shadow active status
    virtual bool getShadowActive() const = 0;

    /// Get the shadow color
    /// \return the shadow color
    virtual jt::Color getShadowColor() const = 0;

    /// Get the shadow offset
    /// \return the offset in pixel
    virtual jt::Vector2f getShadowOffset() const = 0;

    /// Get the outline active status of the drawable
    /// \return the outline active status
    virtual bool getOutlineActive() const = 0;

    /// Get the outline color
    /// \return the outline color
    virtual jt::Color getOutlineColor() const = 0;

    /// Get the outline width
    /// \return the outline width in pixel
    virtual int getOutlineWidth() const = 0;

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

    /// Set the cam movement factor
    /// \param factor the cam movement factor
    virtual void setCamMovementFactor(float factor) = 0;

    /// Get the cam movement factor
    /// \return the cam movement factor
    virtual float getCamMovementFactor() const = 0;

    /// Set the screensize hint. This will be used to avoid drawing of off-screen drawables.
    /// \param hint the size of the screen
    virtual void setScreenSizeHint(jt::Vector2f const& hint) = 0;

    /// Get the stored screensize hint.
    /// \return
    virtual jt::Vector2f getScreenSizeHint() const = 0;

    /// Set the Blend mode
    /// \param mode the blend mode
    virtual void setBlendMode(jt::BlendMode mode) = 0;

    /// Get the Blend mode.
    /// \return the blend mode
    virtual jt::BlendMode getBlendMode() const = 0;

    /// check if is visible, based on ScreenSizeHint
    /// \return true if visible, false if not
    virtual bool isVisible() const = 0;

    /// Set the ZLayer of this drawable. Drawables are drawn in ascending Z order.
    /// Note: You need to add the respective ZLayer first to the GFXInterface via createZLayer().
    /// \param z the z layer.
    virtual void setZ(int z) = 0;

    /// Get the ZLayer of this drawable. Drawables are drawn in ascending Z order.
    /// Note: You need to add the respective ZLayer first to the GFXInterface via createZLayer().
    /// \return the z layer.
    virtual int getZ() const = 0;

    /// Destructor
    virtual ~DrawableInterface() = default;

    // no copy, no move. Avoid slicing.
    DrawableInterface(DrawableInterface const&) = delete;
    DrawableInterface(DrawableInterface&&) = delete;
    DrawableInterface& operator=(DrawableInterface const&) = delete;
    DrawableInterface& operator=(DrawableInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    DrawableInterface() = default;
};
} // namespace jt

#endif
