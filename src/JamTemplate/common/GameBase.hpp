#ifndef GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD

#include "Color.hpp"
#include "GameInterface.hpp"
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

class GameBase : public GameInterface,
                 public GameObject,
                 public std::enable_shared_from_this<GameBase> {
public:
    GameBase();
    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    void switchState(std::shared_ptr<GameState> newState) override;

    std::shared_ptr<GameState> getCurrentSate() override;

    void run() override;

    virtual std::shared_ptr<CamInterface> getCamera() override;
    virtual std::shared_ptr<CamInterface> getCamera() const override;

protected:
    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };

    std::shared_ptr<CamInterface> mutable m_camera { nullptr };

    std::chrono::steady_clock::time_point m_timeLast;

    jt::Color m_backgroundColor { jt::colors::Black };

    std::weak_ptr<GameInterface> getPtr() override;

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override = 0;
    virtual void doDraw() const override = 0;

    virtual void updateShake(float elapsed) = 0;

    void doSwitchState();
};

} // namespace jt

#endif
