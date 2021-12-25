#ifndef GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD

#include "game_interface.hpp"
#include "game_object.hpp"
#include "logging/logger.hpp"
#include "logging/logger_interface.hpp"
#include "render_target.hpp"
#include <chrono>
#include <memory>

namespace jt {
class GameBase : public GameInterface,
                 public GameObject,
                 public std::enable_shared_from_this<GameBase> {
public:
    GameBase(RenderWindowInterface& renderWindow, InputManagerInterface& input,
        MusicPlayerInterface& musicPlayer, CamInterface& camera,
        StateManagerInterface& stateManager);

    void runOneFrame() override;

    RenderWindowInterface& getRenderWindow() const override;

    InputManagerInterface& input() override;

    MusicPlayerInterface& getMusicPlayer() override;

    virtual CamInterface& getCamera() override;
    virtual CamInterface& getCamera() const override;

    StateManagerInterface& getStateManager() override;

    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    std::shared_ptr<jt::TextureManagerInterface> getTextureManager() override;

    LoggerInterface& getLogger() override;

    std::shared_ptr<jt::ActionCommandManagerInterface> getActionCommandManager() override;

    void reset() override;

protected:
    std::weak_ptr<GameInterface> getPtr() override;

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override = 0;
    virtual void doDraw() const override = 0;

    jt::RenderWindowInterface& m_renderWindow;

    InputManagerInterface& m_inputManager;

    CamInterface& m_camera;

    MusicPlayerInterface& m_musicPlayer;

    StateManagerInterface& m_stateManager;

    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };

    std::shared_ptr<jt::TextureManagerInterface> m_textureManager { nullptr };

    mutable jt::Logger m_logger;

    std::shared_ptr<jt::ActionCommandManagerInterface> m_actionCommandManager { nullptr };

    std::chrono::steady_clock::time_point m_timeLast {};
    void createDefaultLogTargets();
};

} // namespace jt

#endif
