#include "main.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "Random.hpp"
#include "StateMenu.hpp"
#include <iostream>
#if ENABLE_WEB
#include <emscripten.h>
#endif

std::shared_ptr<JamTemplate::GameBase> game;

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

    JamTemplate::Random::useTimeAsRandomSeed();

    game = std::make_shared<JamTemplate::Game>(800, 600, 2.0f, GP::GameName());

#if ENABLE_WEB
    game->runGame(std::make_shared<StateMenu>());
    emscripten_set_main_loop(gameloop, 0, 1);
#else
    game->runGame(std::make_shared<StateMenu>());
#endif

    return 0;
}
