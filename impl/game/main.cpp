#include "main.hpp"
#include "game.hpp"
#include "game_properties.hpp"
#include "input_manager.hpp"
#include "keyboard_input.hpp"
#include "mouse_input.hpp"
#include "music_player.hpp"
#include "random.hpp"
#include "render_window.hpp"
#include "state_menu.hpp"

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
    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    auto input = std::make_shared<jt::InputManager>(mouse, keyboard);

    game = std::make_shared<jt::Game>(
        std::make_shared<jt::RenderWindow>(static_cast<unsigned int>(GP::GetWindowSize().x()),
            static_cast<unsigned int>(GP::GetWindowSize().y()), GP::GameName()),
        GP::GetZoom(), input, std::make_shared<jt::MusicPlayer>());
    game->setupRenderTarget();

    game->startGame(std::make_shared<StateMenu>(), gameloop);

    return 0;
}
