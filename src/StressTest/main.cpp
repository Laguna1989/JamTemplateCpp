#include "Game.hpp"
#include "Random.hpp"
#include "RenderWindow_lib.hpp"
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

    game = std::make_shared<jt::Game>(
        std::make_shared<jt::RenderWindow>(800, 600, "Stresstest"), 2.0f, nullptr);
    game->setupRenderTarget();
    game->startGame(std::make_shared<StateSelect>(), gameloop);

    return 0;
}
