#include "camera_helpers.hpp"
#include <algorithm>

namespace {

jt::Vector2f centeredOffset(jt::Vector2f const& target, jt::Vector2f const& screenSize)
{
    return target - screenSize * 0.5f;
}

float clampAxis(float offset, float boundsStart, float boundsLength, float screenLength)
{
    if (boundsLength <= screenLength) {
        return boundsStart + (boundsLength - screenLength) * 0.5f;
    }
    return std::clamp(offset, boundsStart, boundsStart + boundsLength - screenLength);
}

} // namespace

void jt::CameraHelpers::centerOn(
    CamInterface& cam, jt::Vector2f const& target, jt::Vector2f const& screenSize)
{
    cam.setCamOffset(centeredOffset(target, screenSize));
}

void jt::CameraHelpers::followWithMargin(CamInterface& cam, jt::Vector2f const& target,
    jt::Vector2f const& screenSize, float elapsed, float margin, float moveSpeed)
{
    auto const camPos = cam.getCamOffset();
    auto const dif = target - camPos;

    if (dif.x < margin) {
        cam.move(jt::Vector2f { -moveSpeed, 0.0f } * elapsed);
        if (dif.x < margin * 0.5f) {
            cam.move(jt::Vector2f { -moveSpeed, 0.0f } * elapsed);
        }
    }

    if (dif.x > screenSize.x - margin) {
        cam.move(jt::Vector2f { moveSpeed, 0.0f } * elapsed);
        if (dif.x > screenSize.x - margin * 0.5f) {
            cam.move(jt::Vector2f { moveSpeed, 0.0f } * elapsed);
        }
    }

    if (dif.y < margin) {
        cam.move(jt::Vector2f { 0.0f, -moveSpeed } * elapsed);
        if (dif.y < margin * 0.5f) {
            cam.move(jt::Vector2f { 0.0f, -moveSpeed } * elapsed);
        }
    }

    if (dif.y > screenSize.y - margin) {
        cam.move(jt::Vector2f { 0.0f, moveSpeed } * elapsed);
        if (dif.y > screenSize.y - margin * 0.5f) {
            cam.move(jt::Vector2f { 0.0f, moveSpeed } * elapsed);
        }
    }
}

void jt::CameraHelpers::clampToBounds(
    CamInterface& cam, jt::Rectf const& bounds, jt::Vector2f const& screenSize)
{
    auto const offset = cam.getCamOffset();
    cam.setCamOffset(jt::Vector2f { clampAxis(offset.x, bounds.left, bounds.width, screenSize.x),
        clampAxis(offset.y, bounds.top, bounds.height, screenSize.y) });
}
