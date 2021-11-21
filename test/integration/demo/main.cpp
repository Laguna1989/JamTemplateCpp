#include "game.hpp"
#include "input_manager.hpp"
#include "keyboard_input.hpp"
#include "mouse_input.hpp"
#include "random.hpp"
#include "render_window.hpp"
#include "state_select.hpp"
#include <memory>

#include <camera.hpp>
#include <cstdlib>
#include <stdlib.h>

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
    auto camera = std::make_shared<jt::Camera>(2.0f);

    game = std::make_shared<jt::Game>(
        window, input, nullptr, camera, std::make_shared<StateSelect>());
    game->startGame(gameloop);

    return 0;
}
