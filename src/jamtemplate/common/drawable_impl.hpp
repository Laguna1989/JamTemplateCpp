#ifndef GUARD_JAMTEMPLATE_SMARTDRAWABLE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTDRAWABLE_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include "lerp.hpp"
#include "random.hpp"
#include "render_target.hpp"
#include "vector.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace jt {
/// <summary>
///  Implements common functionality of all Drawable classes
/// </summary>
class DrawableImpl : public jt::DrawableInterface {
public:
    using Sptr = std::shared_ptr<DrawableImpl>;

    virtual ~DrawableImpl() = default;

    void draw(std::shared_ptr<jt::renderTarget> sptr) const override;

    void flash(float t, jt::Color col = jt::colors::White) override;

    void shake(float t, float strength, float shakeInterval = 0.05f) override;

    void update(float elapsed) override;

    void setColor(jt::Color const& col) override = 0;
    const jt::Color getColor() const override = 0;

    void setPosition(jt::Vector2 const& pos) override = 0;
    const jt::Vector2 getPosition() const override = 0;

    // virtual sf::Transform const getTransform() const = 0;
    jt::Rect const getGlobalBounds() const override = 0;
    jt::Rect const getLocalBounds() const override = 0;

    void setFlashColor(jt::Color const& col) override = 0;
    const jt::Color getFlashColor() const override = 0;

    void setScale(jt::Vector2 const& scale) override = 0;
    const jt::Vector2 getScale() const override = 0;

    void setOrigin(jt::Vector2 const& origin) override = 0;
    const jt::Vector2 getOrigin() const override = 0;

    jt::Vector2 getOffset() const override;
    void setOffset(jt::Vector2 const offset) override;

    void setRotation(float rot) override;

    float getRotation() const override;

    void setShadowActive(bool active) override;
    bool getShadowActive() const override;
    void setShadowColor(jt::Color const& col) override;
    jt::Color const getShadowColor() const override;
    void setShadowOffset(jt::Vector2 const& v) override;
    jt::Vector2 const getShadowOffset() const override;

    // do not call this manually. Only place to call is Game()->update();
    void setIgnoreCamMovement(bool ignore) override;

    void setShadow(jt::Color const& col, jt::Vector2 const& offset) override;
    // do not call this manually. Only place for this to be called is Game()->update();
    static void setCamOffset(jt::Vector2 const& v) { m_CamOffset = v; }
    static jt::Vector2 getStaticCamOffset() { return m_CamOffset; }

protected:
    jt::Vector2 getShakeOffset() const;

    jt::Vector2 getCamOffset() const;
    bool getIgnoreCamMovement() const;

private:
    static jt::Vector2 m_CamOffset;
    bool m_ignoreCamMovement { false };

    bool m_hasBeenUpdated { false };
    float m_flashTimer { -1.0f };
    float m_maxFlashTimer { -1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::Vector2 m_shakeOffset { 0, 0 };

    jt::Vector2 m_offset { 0, 0 };
    float m_rotationInDegree { 0 };

    bool m_shadowActive { false };
    jt::Vector2 m_shadowOffset { 0.0f, 0.0f };
    jt::Color m_shadowColor { jt::colors::Black };

    virtual void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const = 0;
    virtual void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const = 0;
    virtual void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const = 0;

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

#endif
