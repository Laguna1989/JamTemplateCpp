#ifndef JAMTEMPLATE_CAMERA_HPP
#define JAMTEMPLATE_CAMERA_HPP

#include <cam_interface.hpp>
#include <functional>

namespace jt {
class Camera : public CamInterface {
public:
    /// Constructor
    explicit Camera(float zoom = 1.0f);

    jt::Vector2f getCamOffset() noexcept override;
    void setCamOffset(jt::Vector2f const& ofs) noexcept override;
    void move(jt::Vector2f const& v) noexcept override;

    float getZoom() const noexcept override;
    void setZoom(float zoom) noexcept override;

    void shake(float t, float strength, float shakeInterval = 0.005f) noexcept override;

    jt::Vector2f getShakeOffset() const noexcept override;

    void reset() noexcept override;

    void update(float elapsed) override;

    /// Set random function that will be used to determine the cam displacement
    /// \param randomFunction the random function
    void setRandomFunction(std::function<float(float)> randomFunction);

private:
    jt::Vector2f m_CamOffset { 0.0f, 0.0f };
    float m_zoom { 1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::Vector2f m_shakeOffset { 0, 0 };

    std::function<float(float)> m_randomFunc = nullptr;

    virtual void updateShake(float elapsed);
    virtual void resetShake();
};
} // namespace jt

#endif
