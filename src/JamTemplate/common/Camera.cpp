#include "Camera.hpp"
#include "DrawableImpl.hpp"
#include "Random.hpp"
#include "Rect.hpp"

namespace jt {

Camera::Camera() { }

jt::Vector2 Camera::getCamOffset() { return m_CamOffset; }
void Camera::setCamOffset(jt::Vector2 const& ofs) { m_CamOffset = ofs; }
void Camera::move(jt::Vector2 const& v) { m_CamOffset = m_CamOffset + v; }

float Camera::getZoom() const { return m_zoom; }
void Camera::setZoom(float zoom) { m_zoom = zoom; }

void Camera::shake(float t, float strength, float shakeInterval)
{
    m_shakeTimer = t;
    m_shakeStrength = strength;
    m_shakeInterval = m_shakeIntervalMax = shakeInterval;
}
jt::Vector2 Camera::getShakeOffset() { return m_shakeOffset; }

void Camera::reset()
{
    m_CamOffset = jt::Vector2 { 0.0f, 0.0f };
    resetShake();
}

void Camera::update(float elapsed) { updateShake(elapsed); }

void Camera::updateShake(float elapsed)
{
    if (m_shakeTimer > 0) {
        m_shakeTimer -= elapsed;
        m_shakeInterval -= elapsed;
        if (m_shakeInterval < 0) {
            m_shakeInterval = m_shakeIntervalMax;
            m_shakeOffset.x() = jt::Random::getFloat(-m_shakeStrength, m_shakeStrength);
            m_shakeOffset.y() = jt::Random::getFloat(-m_shakeStrength, m_shakeStrength);
        }
    } else {
        m_shakeOffset.x() = m_shakeOffset.y() = 0;
    }
}

void Camera::resetShake()
{
    m_shakeOffset.x() = m_shakeOffset.y() = 0;
    m_shakeTimer = -1;
    m_shakeStrength = 0;
}

} // namespace jt
