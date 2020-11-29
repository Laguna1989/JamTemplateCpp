#include "Game.hpp"
#include "Random.hpp"
#include "StateTileson.hpp"
#include <memory>

std::shared_ptr<jt::GameBase> game;

void gameloop()
{
    if (game) {
        game->run();
    }
}

int main()
{
    jt::Random::useTimeAsRandomSeed();

    game = std::make_shared<jt::Game>(800, 600, 4.0f, "Stresstest");

    game->runGame(std::make_shared<StateTileson>(), gameloop);

    return 0;
}
