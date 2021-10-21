#ifndef GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD

#include "color.hpp"
#include "game_interface.hpp"
#include "game_loop_interface.hpp"
#include "game_object.hpp"
#include "music_player_interface.hpp"
#include "render_target.hpp"
#include "vector.hpp"
#include <chrono>
#include <memory>

namespace jt {
class GameState;

class GameBase : public GameInterface,
                 public GameObject,
                 public std::enable_shared_from_this<GameBase> {
public:
    GameBase(std::shared_ptr<CamInterface> camera = nullptr);
    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    void switchState(std::shared_ptr<GameState> newState) override;

    std::shared_ptr<GameState> getCurrentState() override;

    void run() override;

    virtual std::shared_ptr<CamInterface> getCamera() override;
    virtual std::shared_ptr<CamInterface> getCamera() const override;

protected:
    std::shared_ptr<GameState> m_state { nullptr };
    std::shared_ptr<GameState> m_nextState { nullptr };

    std::shared_ptr<CamInterface> mutable m_camera { nullptr };

    std::chrono::steady_clock::time_point m_timeLast {};

    jt::Color m_backgroundColor { jt::colors::Black };

    std::weak_ptr<GameInterface> getPtr() override;

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override = 0;
    virtual void doDraw() const override = 0;

    void doSwitchState();
};

} // namespace jt

#endif
