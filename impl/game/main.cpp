#include "main.hpp"
#include <action_commands/action_command_manager.hpp>
#include <action_commands/basic_action_commands.hpp>
#include <audio/audio/audio_impl.hpp>
#include <audio/audio/audio_null.hpp>
#include <cache/cache_impl.hpp>
#include <camera.hpp>
#include <game.hpp>
#include <game_properties.hpp>
#include <gfx_impl.hpp>
#include <graphics/logging_render_window.hpp>
#include <graphics/render_window.hpp>
#include <input/gamepad/gamepad_input.hpp>
#include <input/input_manager.hpp>
#include <input/keyboard/keyboard_input.hpp>
#include <input/mouse/mouse_input.hpp>
#include <log/default_logging.hpp>
#include <log/log_history.hpp>
#include <log/logger.hpp>
#include <logging_camera.hpp>
#include <random/random.hpp>
#include <state_manager/logging_state_manager.hpp>
#include <state_manager/state_manager.hpp>
#include <state_start_with_button.hpp>
#include <memory>

std::shared_ptr<jt::GameBase> game;

void gameloop()
{
    if (game) {
        game->runOneFrame();
    }
}

int main(int /*argc*/, char* /*argv*/[])
{
    hideConsoleInRelease();

    jt::Random::useTimeAsRandomSeed();

    auto logHistory = std::make_shared<jt::LogHistory>();
    jt::CacheImpl cache { nullptr, logHistory };

    jt::Logger logger {};
    jt::createDefaultLogTargets(logger);
    logger.addLogTarget(logHistory);

    jt::RenderWindow window { static_cast<unsigned int>(GP::GetWindowSize().x),
        static_cast<unsigned int>(GP::GetWindowSize().y), GP::GameName() };
    jt::LoggingRenderWindow loggingRenderWindow { window, logger };

    jt::Camera cam { GP::GetZoom() };
    jt::LoggingCamera loggingCamera { cam, logger };
    jt::GfxImpl gfx { loggingRenderWindow, loggingCamera };

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    auto const gamepad0 = std::make_shared<jt::GamepadInput>(0);
    jt::InputManager input { mouse, keyboard, { gamepad0 } };

    jt::AudioImpl audio {};

    jt::StateManager stateManager { std::make_shared<StateStartWithButton>() };
    jt::LoggingStateManager loggingStateManager { stateManager, logger };

    jt::ActionCommandManager actionCommandManager(logger);

    game = std::make_shared<jt::Game>(
        gfx, input, audio, loggingStateManager, logger, actionCommandManager, cache);

    addBasicActionCommands(game);
    game->startGame(gameloop);

    game = nullptr;
    return 0;
}
