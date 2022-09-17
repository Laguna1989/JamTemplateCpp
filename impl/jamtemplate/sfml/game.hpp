﻿#ifndef JAMTEMPLATE_GAME_HPP
#define JAMTEMPLATE_GAME_HPP

#include <game_base.hpp>

namespace jt {

// Actual Game class for SFML
class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    /// Constructor. Will mostly delegate things towards game_base
    /// \param gfx graphics context
    /// \param input input
    /// \param audio audio context
    /// \param stateManager state manager
    /// \param logger logger
    /// \param actionCommandManager action command manager
    Game(GfxInterface& gfx, InputManagerInterface& input, AudioInterface& audio,
        StateManagerInterface& stateManager, LoggerInterface& logger,
        ActionCommandManagerInterface& actionCommandManager, jt::CacheInterface& cache);

    /// Start game
    /// \param gameloop_function
    void startGame(GameLoopFunctionPtr gameloop_function) override;
};

} // namespace jt
#endif
