#include "main.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "InputManager.hpp"
#include "KeyboardInput.hpp"
#include "MouseInput.hpp"
#include "MusicPlayer.hpp"
#include "Random.hpp"
#include "RenderWindow.hpp"
#include "StateMenu.hpp"
#include <iostream>

std::shared_ptr<jt::GameInterface> game;

void gameloop()
{
    if (game) {
        game->run();
    }
}

int main()
{
    // std::cout << "main\n";
    hideConsoleInRelease();

    jt::Random::useTimeAsRandomSeed();
    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    auto input = std::make_shared<jt::InputManager>(mouse, keyboard);
    // TODO Inputmanager nullptr in unit tests

    game = std::make_shared<jt::Game>(std::make_shared<jt::RenderWindow>(GP::GetWindowSize().x(),
                                          GP::GetWindowSize().y(), GP::GameName()),
        GP::GetZoom(), input, std::make_shared<jt::MusicPlayer>());
    game->setupRenderTarget();

    game->startGame(std::make_shared<StateMenu>(), gameloop);

    return 0;
}
