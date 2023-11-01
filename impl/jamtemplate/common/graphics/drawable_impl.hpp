#ifndef JAMTEMPLATE_DRAWABLEIMPL_HPP
#define JAMTEMPLATE_DRAWABLEIMPL_HPP

#include <graphics/drawable_interface.hpp>
#include <graphics/flash_impl.hpp>
#include <graphics/flicker_impl.hpp>
#include <graphics/outline_impl.hpp>
#include <graphics/rotation_impl.hpp>
#include <graphics/shadow_impl.hpp>
#include <graphics/shake_impl.hpp>
#include <vector.hpp>
#include <memory>

namespace jt {

///  Implements common functionality of all Drawable classes
class DrawableImpl :
    //
    public DrawableInterface,
    // implementation of flash, rotation, shadow and shake functionality via mix-in
    private jt::FlashImpl,
    private jt::FlickerImpl,
    private jt::OutlineImpl,
    private jt::RotationImpl,
    private jt::ShadowImpl,
    private jt::ShakeImpl {
public:
    using Sptr = std::shared_ptr<DrawableImpl>;

    /// Destructor
    virtual ~DrawableImpl() = default;

    void draw(std::shared_ptr<jt::RenderTargetInterface> targetContainer) const override;

    void draw(std::shared_ptr<jt::RenderTargetLayer> targets) const;

    void flash(float t, jt::Color col = jt::colors::White) override;
    void shake(float t, float strength, float shakeInterval = 0.05f) override;
    void flicker(float duration, float interval = 0.05f) override;
    void update(float elapsed) override;

    Vector2f getScreenPosition() const override;

    jt::Vector2f getOffset() const override;
    void setOffset(jt::Vector2f const& offset) override;
    OffsetMode getOffsetMode() const override;
    void setOffset(jt::OffsetMode offset) override;

    void setOrigin(Vector2f const& origin) override;
    void setOrigin(jt::OriginMode origin) override;
    OriginMode getOriginMode() const override;
    Vector2f getOrigin() const override;

    void setRotation(float rot) override;
    float getRotation() const override;

    void setFlashColor(Color const& col) override;
    Color getFlashColor() const override;

    bool getOutlineActive() const override;
    void setOutline(jt::Color const& col, int width) override;
    Color getOutlineColor() const override;
    int getOutlineWidth() const override;

    std::vector<jt::Vector2f> getOutlineOffsets() const;

    void setShadow(jt::Color const& col, jt::Vector2f const& offset) override;
    void setShadowActive(bool active) override;

    bool getShadowActive() const override;
    jt::Color getShadowColor() const override;
    jt::Vector2f getShadowOffset() const override;

    void setIgnoreCamMovement(bool ignore) override;
    bool getIgnoreCamMovement() const override;

    /// Get the static camera offset
    /// \return the camera offset
    static jt::Vector2f getStaticCamOffset();

    // do not call this manually. Only place for this to be called is Game()->update();
    static void setCamOffset(jt::Vector2f const& v);

    void setScreenSizeHint(Vector2f const& hint) override;

    Vector2f getScreenSizeHint() const override;

    bool isVisible() const override;

    void setBlendMode(jt::BlendMode mode) override;

    BlendMode getBlendMode() const override;

    void setCamMovementFactor(float factor) override;
    float getCamMovementFactor() const override;

    void setZ(int z) override;
    int getZ() const override;

protected:
    jt::Vector2f getShakeOffset() const;
    jt::Vector2f getCamOffset() const;
    jt::Vector2f m_screenSizeHint { 0.0f, 0.0f };

    virtual void setOriginInternal(jt::Vector2f const& /*origin*/) { }

    float m_camMovementFactor { 1.0f };

    jt::OriginMode m_originMode { jt::OriginMode::MANUAL };
    jt::Vector2f m_origin { 0.0f, 0.0f };

private:
    static jt::Vector2f m_CamOffset;
    bool m_ignoreCamMovement { false };

    bool m_hasBeenUpdated { false };

    jt::OffsetMode m_offsetMode { jt::OffsetMode::MANUAL };
    jt::Vector2f m_offset { 0.0f, 0.0f };

    jt::BlendMode m_blendMode { jt::BlendMode::ALPHA };

    int m_z { 0 };

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) = 0;

    // overwrite this method
    virtual void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_DRAWABLEIMPL_HPP
