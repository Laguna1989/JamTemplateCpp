#include "logging_camera.hpp"

namespace jt {

LoggingCamera::LoggingCamera(CamInterface& decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
    m_logger.info(
        "Camera created, zoom: " + std::to_string(m_decoratee.getZoom()), { "jt", "camera" });
}

Vector2f LoggingCamera::getCamOffset()
{
    m_logger.verbose("getCamOffset", { "jt", "camera" });
    return m_decoratee.getCamOffset();
}

void LoggingCamera::setCamOffset(Vector2f const& newOffset)
{
    m_logger.verbose("setCamOffset", { "jt", "camera" });
    m_decoratee.setCamOffset(newOffset);
}

void LoggingCamera::move(Vector2f const& v)
{
    m_logger.verbose("move", { "jt", "camera" });
    m_decoratee.move(v);
}

float LoggingCamera::getZoom() const
{
    m_logger.verbose("getZoom", { "jt", "camera" });
    return m_decoratee.getZoom();
}

void LoggingCamera::setZoom(float zoom)
{
    m_logger.info("setZoom", { "jt", "camera" });
    m_decoratee.setZoom(zoom);
}

void LoggingCamera::shake(
    float shakeDurationInSeconds, float maxShakeOffsetInPixel, float shakeIntervalInSeconds)
{
    m_logger.info("shake", { "jt", "camera" });
    m_decoratee.shake(shakeDurationInSeconds, maxShakeOffsetInPixel, shakeIntervalInSeconds);
}

Vector2f LoggingCamera::getShakeOffset()
{
    m_logger.verbose("getShakeOffset", { "jt", "camera" });
    return m_decoratee.getShakeOffset();
}

void LoggingCamera::update(float elapsed)
{
    m_logger.verbose("update", { "jt", "camera" });
    m_decoratee.update(elapsed);
}

void LoggingCamera::reset()
{
    m_logger.debug("reset", { "jt", "camera" });
    m_decoratee.reset();
}

} // namespace jt
