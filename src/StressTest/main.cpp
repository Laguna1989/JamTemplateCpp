#include "Game.hpp"
#include "Random.hpp"
#include "StateTileson.hpp"
#include <memory>

std::shared_ptr<JamTemplate::GameBase> game;

void gameloop()
{
    if (game) {
        game->run();
    }
}

int main()
{
    JamTemplate::Random::useTimeAsRandomSeed();

    game = std::make_shared<JamTemplate::Game>(800, 600, 4.0f, "Stresstest");

    game->runGame(std::make_shared<StateTileson>(), gameloop);

    return 0;
}
