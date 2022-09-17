#ifndef JAMTEMPLATE_GAME_HPP
#define JAMTEMPLATE_GAME_HPP

#include <game_base.hpp>
#include <graphics/render_window_interface.hpp>
#include <rect.hpp>
#include <render_target.hpp>
#include <chrono>
#include <memory>
#include <string>

namespace jt {

class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(GfxInterface&, InputManagerInterface& input, AudioInterface& audio,
        StateManagerInterface& stateManager, LoggerInterface& logger,
        ActionCommandManagerInterface& actionCommandManager, CacheInterface& cache);

    void startGame(GameLoopFunctionPtr gameloop_function) override;
};

} // namespace jt
#endif
