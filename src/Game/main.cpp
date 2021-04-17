#include "main.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "MusicPlayer.hpp"
#include "Random.hpp"
#include "RenderWindow_lib.hpp"
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

    game = std::make_shared<jt::Game>(std::make_shared<jt::RenderWindow>(GP::GetWindowSize().x(),
                                          GP::GetWindowSize().y(), GP::GameName()),
        GP::GetZoom(), std::make_shared<jt::MusicPlayer>());
    game->setupRenderTarget();

    game->startGame(std::make_shared<StateMenu>(), gameloop);

    return 0;
}
