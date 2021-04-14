#ifndef GUARD_JAMTEMPLATE_SMARTDRAWABLE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTDRAWABLE_HPP_INCLUDEGUARD

#include "DrawableInterface.hpp"
#include "Lerp.hpp"
#include "Random.hpp"
#include "Rendertarget.hpp"
#include "Vector.hpp"
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

    virtual void draw(std::shared_ptr<jt::renderTarget> sptr) const override;

    virtual void flash(float t, jt::Color col = jt::colors::White) override;

    virtual void shake(float t, float strength, float shakeInterval = 0.05f) override;

    void update(float elapsed) override;

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

    virtual jt::Vector2 getOffset() const override;
    virtual void setOffset(jt::Vector2 const offset) override;

    virtual void setRotation(float rot) override;

    virtual float getRotation() const override;

    virtual void setShadowActive(bool active) override;
    virtual bool getShadowActive() const override;
    virtual void setShadowColor(jt::Color const& col) override;
    virtual jt::Color const getShadowColor() const override;
    virtual void setShadowOffset(jt::Vector2 const& v) override;
    virtual jt::Vector2 const getShadowOffset() const override;

    // do not call this manually. Only place to call is Game()->update();
    virtual void setIgnoreCamMovement(bool ignore) override;

    virtual void setShadow(jt::Color const& col, jt::Vector2 const& offset) override;
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
