#include "camera.hpp"
#include "game.hpp"
#include "input/control_command_interface.hpp"
#include "input/input_manager.hpp"
#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"
#include "music_player_null.hpp"
#include "random/random.hpp"
#include "render_window.hpp"
#include "state_manager.hpp"
#include "state_select.hpp"
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
    jt::Random::useTimeAsRandomSeed();

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    jt::InputManager input { mouse, keyboard };

    jt::RenderWindow window { 800, 600, "jt_demos" };

    jt::MusicPlayerNull music_player;
    jt::Camera camera { 2.0f };

    jt::StateManager stateManager { std::make_shared<StateSelect>() };

    game = std::make_shared<jt::Game>(window, input, music_player, camera, stateManager);
    game->startGame(gameloop);

    game = nullptr;
    return 0;
}
