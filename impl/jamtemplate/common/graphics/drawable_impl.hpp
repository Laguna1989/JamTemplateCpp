﻿#ifndef GUARD_JAMTEMPLATE_DRAWABLEIMPL_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_DRAWABLEIMPL_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include "flash_impl.hpp"
#include "rotation_impl.hpp"
#include "shadow_impl.hpp"
#include "shake_impl.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {

///  Implements common functionality of all Drawable classes
class DrawableImpl :
    //
    public DrawableInterface,
    // implementation of flash, rotation, shadow and shake functionality via mix-in
    private jt::FlashImpl,
    private jt::RotationImpl,
    private jt::ShadowImpl,
    private jt::ShakeImpl {
public:
    using Sptr = std::shared_ptr<DrawableImpl>;

    /// Destructor
    virtual ~DrawableImpl() = default;
    void draw(std::shared_ptr<RenderTarget> sptr) const override;

    void flash(float t, jt::Color col = jt::colors::White) override;
    void shake(float t, float strength, float shakeInterval = 0.05f) override;

    void update(float elapsed) override;

    jt::Vector2f getOffset() const override;
    void setOffset(jt::Vector2f const offset) override;

    void setRotation(float rot) override;
    float getRotation() const override;

    void setFlashColor(Color const& col) override;
    Color getFlashColor() const override;

    void setShadow(jt::Color const& col, jt::Vector2f const& offset) override;
    void setShadowActive(bool active) override;

    bool getShadowActive() const override;
    jt::Color getShadowColor() const override;
    jt::Vector2f getShadowOffset() const override;

    void setIgnoreCamMovement(bool ignore) override;
    bool getIgnoreCamMovement() const override;

    static jt::Vector2f getStaticCamOffset();

    // do not call this manually. Only place for this to be called is Game()->update();
    static void setCamOffset(jt::Vector2f const& v);

    void setScreenSizeHint(Vector2f const& hint) override;

    virtual bool isVisible() const;

protected:
    jt::Vector2f getShakeOffset() const;
    jt::Vector2f getCamOffset() const;
    jt::Vector2f m_screenSizeHint { 0.0f, 0.0f };

private:
    static jt::Vector2f m_CamOffset;
    bool m_ignoreCamMovement { false };

    bool m_hasBeenUpdated { false };

    jt::Vector2f m_offset { 0, 0 };

    // overwrite this method
    virtual void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const = 0;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) = 0;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_DRAWABLEIMPL_HPP_INCLUDEGUARD
