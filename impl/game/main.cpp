#include "main.hpp"
#include "action_commands/action_command_manager.hpp"
#include "action_commands/basic_action_commands.hpp"
#include "audio/audio_impl.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "game_properties.hpp"
#include "gfx_impl.hpp"
#include "input/input_manager.hpp"
#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"
#include "logging/default_logging.hpp"
#include "logging/logger.hpp"
#include "random/random.hpp"
#include "render_window.hpp"
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

    jt::GfxImpl gfx { jt::RenderWindow { static_cast<unsigned int>(GP::GetWindowSize().x),
                          static_cast<unsigned int>(GP::GetWindowSize().y), GP::GameName() },
        jt::Camera { GP::GetZoom() } };

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    jt::InputManager input { mouse, keyboard };

    jt::AudioImpl audio;

    jt::StateManager stateManager { std::make_shared<StateMenu>() };
    jt::Logger logger;
    jt::createDefaultLogTargets(logger);
    jt::ActionCommandManager actionCommandManager(logger);

    game
        = std::make_shared<jt::Game>(gfx, input, audio, stateManager, logger, actionCommandManager);

    addBasicActionCommands(game);
    game->startGame(gameloop);

    game = nullptr;
    return 0;
}
