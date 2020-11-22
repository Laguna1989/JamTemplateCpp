#include "main.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "Random.hpp"
#include "StateMenu.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    hideConsoleInRelease();

    JamTemplate::Random::useTimeAsRandomSeed();

    auto game = std::make_shared<JamTemplate::Game>(800, 600, 2.0f, GP::GameName());
    game->runGame(std::make_shared<StateMenu>());

    return 0;
}
