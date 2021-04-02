#ifndef GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD

#include "Color.hpp"
#include "GameLoopInterface.hpp"
#include "GameObject.hpp"
#include "MusicPlayerInterface.hpp"
#include "Rendertarget.hpp"
#include "Vector.hpp"
#include <chrono>
#include <functional>
#include <memory>

namespace jt {
class GameState;

class GameInterface : public GameLoopInterface {
public:
    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() = 0;

    // cannot be const because getView is not const
    virtual jt::Vector2 getCamOffset() = 0;
    virtual void setCamOffset(jt::Vector2 const& ofs) = 0;
    virtual void moveCam(jt::Vector2 const& v) = 0;
    virtual float getZoom() const = 0;
    virtual void shake(float t, float strength, float shakeInterval = 0.005f) = 0;

    virtual void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) = 0;
    virtual std::shared_ptr<jt::renderTarget> getRenderTarget() const = 0;

protected:
    virtual std::weak_ptr<GameInterface> getPtr() = 0;
};

} // namespace jt

#endif
