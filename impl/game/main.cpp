#include "main.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "game_properties.hpp"
#include "input_manager.hpp"
#include "keyboard_input.hpp"
#include "mouse_input.hpp"
#include "music_player.hpp"
#include "random.hpp"
#include "render_window.hpp"
#include "state_menu.hpp"
#include <memory>
#include <state_manager.hpp>

std::shared_ptr<jt::GameInterface> game;

void gameloop()
{
    if (game) {
        game->run();
    }
}

int main()
{
    hideConsoleInRelease();

    jt::Random::useTimeAsRandomSeed();
    auto window
        = std::make_shared<jt::RenderWindow>(static_cast<unsigned int>(GP::GetWindowSize().x()),
            static_cast<unsigned int>(GP::GetWindowSize().y()), GP::GameName());

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    auto input = std::make_shared<jt::InputManager>(mouse, keyboard);

    std::shared_ptr<jt::MusicPlayer> musicPlayer = std::make_shared<jt::MusicPlayer>();
    auto camera = std::make_shared<jt::Camera>(GP::GetZoom());
    auto stateManager = std::make_shared<jt::StateManager>(std::make_shared<StateMenu>());

    game = std::make_shared<jt::Game>(window, input, musicPlayer, camera, stateManager);
    game->startGame(gameloop);

    return 0;
}
