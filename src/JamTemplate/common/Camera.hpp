#ifndef GUARD_JAMTEMPLATE_CAMERA_HPP_GUARD
#define GUARD_JAMTEMPLATE_CAMERA_HPP_GUARD

#include "CamInterface.hpp"

namespace jt {
class Camera : public CamInterface {
public:
    Camera();

    virtual jt::Vector2 getCamOffset() override;
    virtual void setCamOffset(jt::Vector2 const& ofs) override;
    virtual void move(jt::Vector2 const& v) override;

    virtual float getZoom() const override;
    virtual void setZoom(float zoom) override;

    virtual void shake(float t, float strength, float shakeInterval = 0.005f) override;
    virtual jt::Vector2 getShakeOffset() override;

    virtual void reset() override;

    virtual void update(float elapsed) override;

private:
    jt::Vector2 m_CamOffset { 0.0f, 0.0f };
    float m_zoom { 1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::Vector2 m_shakeOffset { 0, 0 };

    virtual void updateShake(float elapsed);
    virtual void resetShake();
};
} // namespace jt

#endif
