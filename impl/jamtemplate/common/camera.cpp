#include "camera.hpp"
#include <random/random.hpp>
#include <stdexcept>

jt::Camera::Camera(float zoom)
{
    Camera::setZoom(zoom);
    m_randomFunc = [](float max) { return Random::getFloat(-max, max); };
};

jt::Vector2f jt::Camera::getCamOffset() noexcept { return m_CamOffset; }

void jt::Camera::setCamOffset(jt::Vector2f const& ofs) noexcept { m_CamOffset = ofs; }

void jt::Camera::move(jt::Vector2f const& v) noexcept { m_CamOffset = m_CamOffset + v; }

float jt::Camera::getZoom() const noexcept { return m_zoom; }

void jt::Camera::setZoom(float zoom) noexcept { m_zoom = zoom; }

void jt::Camera::shake(float t, float strength, float shakeInterval) noexcept
{
    m_shakeTimer = t;
    m_shakeStrength = strength;
    m_shakeInterval = m_shakeIntervalMax = shakeInterval;
}

jt::Vector2f jt::Camera::getShakeOffset() const noexcept { return m_shakeOffset; }

void jt::Camera::reset() noexcept
{
    m_CamOffset = jt::Vector2f { 0.0f, 0.0f };
    resetShake();
}

void jt::Camera::update(float elapsed) { updateShake(elapsed); }

void jt::Camera::updateShake(float elapsed)
{
    m_shakeTimer -= elapsed;
    if (m_shakeTimer > 0) {
        m_shakeInterval -= elapsed;
        if (m_shakeInterval < 0) {
            m_shakeInterval = m_shakeIntervalMax;
            m_shakeOffset.x = m_randomFunc(m_shakeStrength);
            m_shakeOffset.y = m_randomFunc(m_shakeStrength);
        }
    } else {
        m_shakeOffset.x = m_shakeOffset.y = 0;
    }
}

void jt::Camera::resetShake()
{
    m_shakeOffset.x = m_shakeOffset.y = 0;
    m_shakeTimer = -1;
    m_shakeStrength = 0;
}

void jt::Camera::setRandomFunction(std::function<float(float)> randomFunc)
{
    if (!randomFunc) {
        throw std::invalid_argument { "Can not set nullptr random function for Camera" };
    }
    m_randomFunc = randomFunc;
}
