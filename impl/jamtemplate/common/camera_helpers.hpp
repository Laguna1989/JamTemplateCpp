#ifndef JAMTEMPLATE_CAMERA_HELPERS_HPP
#define JAMTEMPLATE_CAMERA_HELPERS_HPP

#include <cam_interface.hpp>
#include <rect.hpp>
#include <vector.hpp>

namespace jt {

namespace CameraHelpers {

/// Instantly move the camera so that target is in the center of the screen
/// \param cam the camera to move
/// \param target the position (in world coordinates) to center on
/// \param screenSize the visible area in world coordinates (i.e. window size divided by zoom)
void centerOn(CamInterface& cam, jt::Vector2f const& target, jt::Vector2f const& screenSize);

/// Scroll the camera when target gets close to the screen edges. While target is further than
/// margin away from all screen edges, the camera does not move. Within margin, the camera moves
/// with moveSpeed on that axis, within margin / 2 with twice the moveSpeed.
/// \param cam the camera to move
/// \param target the position (in world coordinates) to follow
/// \param screenSize the visible area in world coordinates (i.e. window size divided by zoom)
/// \param elapsed the elapsed time in seconds
/// \param margin distance (in world coordinates) from the screen edges at which scrolling starts
/// \param moveSpeed scroll speed in world coordinates per second
void followWithMargin(CamInterface& cam, jt::Vector2f const& target,
    jt::Vector2f const& screenSize, float elapsed, float margin = 100.0f, float moveSpeed = 90.0f);

/// Clamp the camera so that the visible area stays within bounds. If bounds are smaller than
/// the screen on an axis, the bounds are centered on that axis.
/// \param cam the camera to clamp
/// \param bounds the area (in world coordinates) the camera should not leave, e.g. the level
/// \param screenSize the visible area in world coordinates (i.e. window size divided by zoom)
void clampToBounds(CamInterface& cam, jt::Rectf const& bounds, jt::Vector2f const& screenSize);

} // namespace CameraHelpers

} // namespace jt

#endif // JAMTEMPLATE_CAMERA_HELPERS_HPP
