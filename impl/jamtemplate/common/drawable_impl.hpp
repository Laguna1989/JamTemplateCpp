#ifndef GUARD_JAMTEMPLATE_DRAWABLEIMPL_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_DRAWABLEIMPL_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {

///  Implements common functionality of all Drawable classes
class DrawableImpl : public DrawableInterface {
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

    void setShadowActive(bool active) override;
    bool getShadowActive() const override;
    void setShadowColor(jt::Color const& col) override;
    jt::Color getShadowColor() const override;
    void setShadowOffset(jt::Vector2f const& v) override;
    jt::Vector2f getShadowOffset() const override;

    // do not call this manually. Only place to call is Game()->update();
    void setIgnoreCamMovement(bool ignore) override;
    bool getIgnoreCamMovement() const override;

    void setShadow(jt::Color const& col, jt::Vector2f const& offset) override;
    // do not call this manually. Only place for this to be called is Game()->update();
    static void setCamOffset(jt::Vector2f const& v);
    static jt::Vector2f getStaticCamOffset();

protected:
    jt::Vector2f getShakeOffset() const;

    jt::Vector2f getCamOffset() const;

private:
    static jt::Vector2f m_CamOffset;
    bool m_ignoreCamMovement { false };

    bool m_hasBeenUpdated { false };
    float m_flashTimer { -1.0f };
    float m_maxFlashTimer { -1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::Vector2f m_shakeOffset { 0, 0 };

    jt::Vector2f m_offset { 0, 0 };
    float m_rotationInDegree { 0 };

    bool m_shadowActive { false };
    jt::Vector2f m_shadowOffset { 0.0f, 0.0f };
    jt::Color m_shadowColor { jt::colors::Black };

    virtual void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const = 0;
    virtual void doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const = 0;
    virtual void doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const = 0;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) = 0;
    virtual void doFlash(float /*t*/, jt::Color /*col = jt::colors::White*/) { }
    virtual void doRotate(float /*rot*/) = 0;

    void updateFlash(float elapsed);

    void updateShake(float elapsed);
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_DRAWABLEIMPL_HPP_INCLUDEGUARD
