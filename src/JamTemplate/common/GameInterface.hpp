#ifndef GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD

#include "CamInterface.hpp"
#include "GameLoopInterface.hpp"
#include "InputManagerInterface.hpp"
#include "MusicPlayerInterface.hpp"
#include "Rendertarget.hpp"
#include "Vector.hpp"
#include <memory>

namespace jt {
class GameState;

class GameInterface : public GameLoopInterface {
public:
    virtual std::shared_ptr<InputManagerInterface> input() = 0;

    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() = 0;

    virtual std::shared_ptr<CamInterface> getCamera() = 0;
    virtual std::shared_ptr<CamInterface> getCamera() const = 0;

    virtual void setupRenderTarget() = 0;
    virtual void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) = 0;
    virtual std::shared_ptr<jt::renderTarget> getRenderTarget() const = 0;

protected:
    virtual std::weak_ptr<GameInterface> getPtr() = 0;
};

} // namespace jt

#endif
