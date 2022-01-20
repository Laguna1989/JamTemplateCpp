#include "action_commands/action_command_manager.hpp"
#include "action_commands/basic_action_commands.hpp"
#include "audio/audio_null.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "gfx_impl.hpp"
#include "input/input_manager.hpp"
#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"
#include "logging/default_logging.hpp"
#include "logging/logger.hpp"
#include "random/random.hpp"
#include "render_window.hpp"
#include "state_manager/state_manager.hpp"
#include "state_select.hpp"
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
    jt::Random::useTimeAsRandomSeed();

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    jt::InputManager input { mouse, keyboard };

    jt::RenderWindow window { 800, 600, "jt_demos" };
    jt::Camera camera { 2.0f };
    jt::GfxImpl gfx { std::move(window), std::move(camera) };

    jt::AudioNull audio;

    jt::StateManager stateManager { std::make_shared<StateSelect>() };

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
