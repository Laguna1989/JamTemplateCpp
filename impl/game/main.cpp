#include "main.hpp"
#include "action_commands/action_command_manager.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "game_properties.hpp"
#include "input/input_manager.hpp"
#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"
#include "music_player.hpp"
#include "random/random.hpp"
#include "render_window.hpp"
#include "state_manager.hpp"
#include "state_menu.hpp"
#include <memory>

std::shared_ptr<jt::GameInterface> game;

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
    jt::RenderWindow window { static_cast<unsigned int>(GP::GetWindowSize().x),
        static_cast<unsigned int>(GP::GetWindowSize().y), GP::GameName() };

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    jt::InputManager input { mouse, keyboard };

    jt::MusicPlayer musicPlayer;
    jt::Camera camera { GP::GetZoom() };
    jt::StateManager stateManager { std::make_shared<StateMenu>() };
    jt::Logger logger;
    jt::ActionCommandManager actionCommandManager(logger);

    game = std::make_shared<jt::Game>(
        window, input, musicPlayer, camera, stateManager, logger, actionCommandManager);
    game->startGame(gameloop);

    game = nullptr;
    return 0;
}
