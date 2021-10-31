#ifndef GUARD_JAMTEMPLATE_CAMERA_HPP_GUARD
#define GUARD_JAMTEMPLATE_CAMERA_HPP_GUARD

#include "cam_interface.hpp"
#include <functional>

namespace jt {
class Camera : public CamInterface {
public:
    /// Constructor
    Camera();

    jt::Vector2 getCamOffset() override;
    void setCamOffset(jt::Vector2 const& ofs) override;
    void move(jt::Vector2 const& v) override;

    float getZoom() const override;
    void setZoom(float zoom) override;

    void shake(float t, float strength, float shakeInterval = 0.005f) override;

    jt::Vector2 getShakeOffset() override;

    void reset() override;

    void update(float elapsed) override;

    /// Set random function that will be used to determine the cam displacement
    /// \param randomFunction the random function
    void setRandomFunction(std::function<float(float)> randomFunction);

private:
    jt::Vector2 m_CamOffset { 0.0f, 0.0f };
    float m_zoom { 1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::Vector2 m_shakeOffset { 0, 0 };

    std::function<float(float)> m_randomFunc = nullptr;

    virtual void updateShake(float elapsed);
    virtual void resetShake();
    void setDefaultRandomFunction();
};
} // namespace jt

#endif
