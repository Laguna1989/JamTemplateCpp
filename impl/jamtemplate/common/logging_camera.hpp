#ifndef JAMTEMPLATE_LOGGING_CAMERA_HPP
#define JAMTEMPLATE_LOGGING_CAMERA_HPP

#include <cam_interface.hpp>
#include <log/logger_interface.hpp>

namespace jt {
class LoggingCamera : public CamInterface {
public:
    LoggingCamera(CamInterface& decoratee, LoggerInterface& logger);
    jt::Vector2f getCamOffset() override;
    void setCamOffset(jt::Vector2f const& newOffset) override;
    void move(jt::Vector2f const& v) override;
    float getZoom() const override;
    void setZoom(float zoom) override;
    void shake(float shakeDurationInSeconds, float maxShakeOffsetInPixel,
        float shakeIntervalInSeconds) override;
    jt::Vector2f getShakeOffset() const override;
    void update(float elapsed) override;
    void reset() override;

private:
    CamInterface& m_decoratee;
    LoggerInterface& m_logger;
};
} // namespace jt
#endif // JAMTEMPLATE_LOGGING_CAMERA_HPP
