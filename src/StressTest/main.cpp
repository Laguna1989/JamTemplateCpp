#include "Game.hpp"
#include "Random.hpp"
#include "StateSelect.hpp"
#include <iostream>
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

    game = std::make_shared<jt::Game>(800, 600, 2.0f, "Stresstest", nullptr);

    game->startGame(std::make_shared<StateSelect>(), gameloop);

    return 0;
}
