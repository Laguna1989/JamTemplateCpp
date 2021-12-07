#ifndef GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEBASE_HPP_GUARD

#include "game_interface.hpp"
#include "game_object.hpp"
#include "logging/console.hpp"
#include "logging/logger_interface.hpp"
#include "music_player_interface.hpp"
#include "render_target.hpp"
#include "vector.hpp"
#include <chrono>
#include <memory>

namespace jt {
class GameBase : public GameInterface,
                 public GameObject,
                 public std::enable_shared_from_this<GameBase> {
public:
    GameBase(std::shared_ptr<jt::RenderWindowInterface> renderWindow,
        std::shared_ptr<InputManagerInterface> input,
        std::shared_ptr<MusicPlayerInterface> musicPlayer, std::shared_ptr<CamInterface> camera,
        std::shared_ptr<StateManagerInterface> stateManager);

    void run() override;

    std::shared_ptr<jt::RenderWindowInterface> getRenderWindow() const override;

    std::shared_ptr<InputManagerInterface> input() override;

    std::shared_ptr<MusicPlayerInterface> getMusicPlayer() override;

    virtual std::shared_ptr<CamInterface> getCamera() override;
    virtual std::shared_ptr<CamInterface> getCamera() const override;

    std::shared_ptr<StateManagerInterface> getStateManager() override;

    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    std::shared_ptr<jt::TextureManagerInterface> getTextureManager() override;

    std::shared_ptr<jt::LoggerInterface> getLogger() override;

    void reset() override;

protected:
    std::shared_ptr<jt::RenderWindowInterface> m_renderWindow { nullptr };

    std::shared_ptr<InputManagerInterface> m_inputManager { nullptr };

    std::shared_ptr<CamInterface> mutable m_camera { nullptr };

    std::shared_ptr<MusicPlayerInterface> m_musicPlayer { nullptr };

    std::shared_ptr<StateManagerInterface> m_stateManager { nullptr };

    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };

    std::shared_ptr<jt::TextureManagerInterface> m_textureManager { nullptr };

    std::shared_ptr<jt::LoggerInterface> m_logger { nullptr };

    std::chrono::steady_clock::time_point m_timeLast {};

    std::weak_ptr<GameInterface> getPtr() override;

    // overwritten functions from GameObject
    virtual void doUpdate(float const elapsed) override = 0;
    virtual void doDraw() const override = 0;
};

} // namespace jt

#endif
