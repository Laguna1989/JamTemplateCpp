#ifndef GUARD_JAMTEMPLATE_CAMINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_CAMINTERFACE_HPP_GUARD

#include "Rendertarget.hpp"
#include "Vector.hpp"
#include <memory>

namespace jt {

class CamInterface {
public:
    virtual jt::Vector2 getCamOffset() = 0;
    virtual void setCamOffset(jt::Vector2 const& ofs) = 0;
    virtual void move(jt::Vector2 const& v) = 0;
    virtual float getZoom() const = 0;
    virtual void setZoom(float zoom) = 0;

    virtual void shake(float t, float strength, float shakeInterval = 0.005f) = 0;
    virtual jt::Vector2 getShakeOffset() = 0;

    virtual void update(float elapsed) = 0;
    virtual void reset() = 0;
};
} // namespace jt
#endif
