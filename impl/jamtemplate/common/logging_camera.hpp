#ifndef GUARD_JAMTEMPLATE_LOGGING_CAMERA_HPP
#define GUARD_JAMTEMPLATE_LOGGING_CAMERA_HPP

#include "cam_interface.hpp"
#include "logging/logger_interface.hpp"

namespace jt {
class LoggingCamera : public CamInterface {
public:
    LoggingCamera(CamInterface& decoratee, LoggerInterface& logger);
    Vector2f getCamOffset() override;
    void setCamOffset(Vector2f const& newOffset) override;
    void move(Vector2f const& v) override;
    float getZoom() const override;
    void setZoom(float zoom) override;
    void shake(float shakeDurationInSeconds, float maxShakeOffsetInPixel,
        float shakeIntervalInSeconds) override;
    Vector2f getShakeOffset() override;
    void update(float elapsed) override;
    void reset() override;

private:
    CamInterface& m_decoratee;
    LoggerInterface& m_logger;
};
} // namespace jt
#endif // GUARD_JAMTEMPLATE_LOGGING_CAMERA_HPP
