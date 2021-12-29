#ifndef GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD

#include "game_interface.hpp"
#include "game_object.hpp"
#include "logging/logger.hpp"
#include "logging/logger_interface.hpp"
#include "render_target.hpp"
#include "texture_manager_impl.hpp"
#include <chrono>
#include <memory>
#include <optional>

namespace jt {
class GameBase : public GameInterface,
                 public GameObject,
                 public std::enable_shared_from_this<GameBase> {
public:
    GameBase(GfxInterface& gfx, InputManagerInterface& input, MusicPlayerInterface& musicPlayer,
        StateManagerInterface& stateManager, LoggerInterface& logger,
        ActionCommandManagerInterface& actionCommandManager);

    void runOneFrame() override;

    GfxInterface& gfx() const override;

    InputManagerInterface& input() override;

    MusicPlayerInterface& getMusicPlayer() override;

    virtual CamInterface& getCamera() override;
    virtual CamInterface& getCamera() const override;

    StateManagerInterface& getStateManager() override;

    std::shared_ptr<renderTarget> getRenderTarget() const override;

    LoggerInterface& getLogger() override;

    ActionCommandManagerInterface& getActionCommandManager() override;

    void reset() override;

protected:
    std::weak_ptr<GameInterface> getPtr() override;

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override = 0;
    virtual void doDraw() const override = 0;

    GfxInterface& m_gfx;

    InputManagerInterface& m_inputManager;

    MusicPlayerInterface& m_musicPlayer;

    StateManagerInterface& m_stateManager;

    LoggerInterface& m_logger;

    ActionCommandManagerInterface& m_actionCommandManager;

    std::chrono::steady_clock::time_point m_timeLast {};
};

} // namespace jt

#endif
