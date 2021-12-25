#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "game_base.hpp"
#include "render_target.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>

namespace jt {

// Actual Game class for SFML
class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    /// Constructor
    /// \param window window
    /// \param input input manager
    /// \param musicPlayer music player
    /// \param camera camera
    /// \param stateManager state manager
    Game(RenderWindowInterface& window, InputManagerInterface& input,
        MusicPlayerInterface& musicPlayer, std::shared_ptr<CamInterface> camera,
        std::shared_ptr<jt::StateManagerInterface> stateManager);

    void startGame(GameLoopFunctionPtr gameloop_function) override;

private:
    std::shared_ptr<sf::View> m_view { nullptr };

    mutable std::unique_ptr<jt::Sprite> m_sprite_for_drawing { nullptr };

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void setupRenderTarget();
};

} // namespace jt
#endif
