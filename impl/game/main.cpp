#include "main.hpp"
#include "action_commands/action_command_manager.hpp"
#include "action_commands/basic_action_commands.hpp"
#include "audio/audio_impl.hpp"
#include "audio/logging_audio_decorator.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "game_properties.hpp"
#include "gfx_impl.hpp"
#include "graphics/logging_render_window_decorator.hpp"
#include "graphics/render_window.hpp"
#include "input/input_manager.hpp"
#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"
#include "logging/default_logging.hpp"
#include "logging/logger.hpp"
#include "random/random.hpp"
#include "state_manager/logging_state_manager_decorator.hpp"
#include "state_manager/state_manager.hpp"
#include "state_menu.hpp"
#include <memory>

std::shared_ptr<jt::GameBase> game;

void gameloop()
{
    if (game) {
        game->runOneFrame();
    }
}

int main()
{
    hideConsoleInRelease();

    jt::Random::useTimeAsRandomSeed();

    jt::Logger logger;
    jt::createDefaultLogTargets(logger);

    jt::RenderWindow window { static_cast<unsigned int>(GP::GetWindowSize().x),
        static_cast<unsigned int>(GP::GetWindowSize().y), GP::GameName() };
    jt::LoggingRenderWindowDecorator loggingRenderWindow { window, logger };
    jt::Camera cam { GP::GetZoom() };
    jt::GfxImpl gfx { loggingRenderWindow, cam };

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    jt::InputManager input { mouse, keyboard };

    jt::AudioImpl audio;
    jt::LoggingAudioDecorator loggingAudio { audio, logger };

    jt::StateManager stateManager { std::make_shared<StateMenu>() };
    jt::LoggingStateManagerDecorator loggingStateManager { stateManager, logger };

    jt::ActionCommandManager actionCommandManager(logger);

    game = std::make_shared<jt::Game>(
        gfx, input, loggingAudio, loggingStateManager, logger, actionCommandManager);

    addBasicActionCommands(game);
    game->startGame(gameloop);

    game = nullptr;
    return 0;
}
