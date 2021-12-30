#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "game_base.hpp"

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
    Game(GfxInterface& gfx, InputManagerInterface& input, MusicPlayerInterface& musicPlayer,
        StateManagerInterface& stateManager, LoggerInterface& logger,
        ActionCommandManagerInterface& actionCommandManager);

    void startGame(GameLoopFunctionPtr gameloop_function) override;
};

} // namespace jt
#endif
