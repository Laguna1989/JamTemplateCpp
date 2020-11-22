#include "Game.hpp"
#include "State1.hpp"
#include "StateBox2d.hpp"
#include "StateTileson.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <numeric>

int main()
{
    JamTemplate::Game::Sptr game
        = std::make_shared<JamTemplate::Game>(800, 600, 4.0f, "Stresstest");
    game->runGame(std::make_shared<StateTileson>());

    return 0;
}
