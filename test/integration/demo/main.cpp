#include "camera.hpp"
#include "game.hpp"
#include "input_manager.hpp"
#include "keyboard_input.hpp"
#include "mouse_input.hpp"
#include "music_player_null.hpp"
#include "random.hpp"
#include "render_window.hpp"
#include "state_select.hpp"
#include <memory>

std::shared_ptr<jt::GameInterface> game;

void gameloop()
{
    if (game) {
        game->run();
    }
}

int main()
{
    jt::Random::useTimeAsRandomSeed();

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    auto input = std::make_shared<jt::InputManager>(mouse, keyboard);

    auto window = std::make_shared<jt::RenderWindow>(800, 600, "jt_demos");

    auto music_player = std::make_shared<jt::MusicPlayerNull>();
    auto camera = std::make_shared<jt::Camera>(2.0f);

    game = std::make_shared<jt::Game>(
        window, input, music_player, camera, std::make_shared<StateSelect>());
    game->startGame(gameloop);

    return 0;
}
