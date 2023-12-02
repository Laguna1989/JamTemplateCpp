#include "logging_camera.hpp"

jt::LoggingCamera::LoggingCamera(jt::CamInterface& decoratee, jt::LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
    m_logger.info(
        "Camera created, zoom: " + std::to_string(m_decoratee.getZoom()), { "jt", "camera" });
}

jt::Vector2f jt::LoggingCamera::getCamOffset()
{
    m_logger.verbose("getCamOffset", { "jt", "camera" });
    return m_decoratee.getCamOffset();
}

void jt::LoggingCamera::setCamOffset(jt::Vector2f const& newOffset)
{
    m_logger.verbose("setCamOffset", { "jt", "camera" });
    m_decoratee.setCamOffset(newOffset);
}

void jt::LoggingCamera::move(jt::Vector2f const& v)
{
    m_logger.verbose("move", { "jt", "camera" });
    m_decoratee.move(v);
}

float jt::LoggingCamera::getZoom() const
{
    m_logger.verbose("getZoom", { "jt", "camera" });
    return m_decoratee.getZoom();
}

void jt::LoggingCamera::setZoom(float zoom)
{
    m_logger.info("setZoom", { "jt", "camera" });
    m_decoratee.setZoom(zoom);
}

void jt::LoggingCamera::shake(
    float shakeDurationInSeconds, float maxShakeOffsetInPixel, float shakeIntervalInSeconds)
{
    m_logger.debug("shake", { "jt", "camera" });
    m_decoratee.shake(shakeDurationInSeconds, maxShakeOffsetInPixel, shakeIntervalInSeconds);
}

jt::Vector2f jt::LoggingCamera::getShakeOffset() const
{
    m_logger.verbose("getShakeOffset", { "jt", "camera" });
    return m_decoratee.getShakeOffset();
}

void jt::LoggingCamera::update(float elapsed)
{
    m_logger.verbose("update", { "jt", "camera" });
    m_decoratee.update(elapsed);
}

void jt::LoggingCamera::reset()
{
    m_logger.debug("reset", { "jt", "camera" });
    m_decoratee.reset();
}
