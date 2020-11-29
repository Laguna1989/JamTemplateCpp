#include "main.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "Random.hpp"
#include "StateMenu.hpp"
#include <iostream>

std::shared_ptr<jt::GameBase> game;

void gameloop()
{
    if (game) {
        game->run();
    }
}

int main()
{
    std::cout << "main\n";
    hideConsoleInRelease();

    jt::Random::useTimeAsRandomSeed();

    game = std::make_shared<jt::Game>(800, 600, 2.0f, GP::GameName());

    game->runGame(std::make_shared<StateMenu>(), gameloop);

    return 0;
}
