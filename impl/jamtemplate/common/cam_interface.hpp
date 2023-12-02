#ifndef JAMTEMPLATE_CAMINTERFACE_HPP
#define JAMTEMPLATE_CAMINTERFACE_HPP

#include <vector.hpp>

namespace jt {

class CamInterface {
public:
    /// Get the camera offset (e.g. from scrolling)
    /// \return the camera offset
    virtual jt::Vector2f getCamOffset() = 0;

    /// Set the camera offset
    /// \param newOffset
    virtual void setCamOffset(jt::Vector2f const& newOffset) = 0;

    /// Move the camera by a certain vector
    /// \param v amount that camera should be moved
    virtual void move(jt::Vector2f const& v) = 0;

    /// Get the current zoom value
    /// \return the zoom value
    virtual float getZoom() const = 0;

    /// Set the zoom value
    /// \param zoom
    virtual void setZoom(float zoom) = 0;

    /// Shake the camera
    /// \param shakeDurationInSeconds how long the shake will last
    /// \param maxShakeOffsetInPixel how strong the shake will be
    /// \param shakeIntervalInSeconds how often a new shake offset will be selected
    virtual void shake(float shakeDurationInSeconds, float maxShakeOffsetInPixel,
        float shakeIntervalInSeconds = 0.005f)
        = 0;

    /// Get the shakeOffset of the camera
    /// \return the current shake offset
    virtual jt::Vector2f getShakeOffset() const = 0;

    /// Update the camera
    /// \param elapsed the elapsed time
    virtual void update(float elapsed) = 0;

    /// Reset the camera
    virtual void reset() = 0;

    virtual ~CamInterface() = default;

    // no copy, no move. Avoid slicing.
    CamInterface(CamInterface const&) = delete;
    CamInterface(CamInterface&&) = delete;
    CamInterface& operator=(CamInterface const&) = delete;
    CamInterface& operator=(CamInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    CamInterface() = default;
};
} // namespace jt
#endif
