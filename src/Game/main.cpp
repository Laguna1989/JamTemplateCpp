#include "main.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "MusicPlayer.hpp"
#include "Random.hpp"
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

    game = std::make_shared<jt::Game>(static_cast<unsigned int>(GP::GetWindowSize().x()),
        static_cast<float>(GP::GetWindowSize().y()), GP::GetZoom(), GP::GameName(),
        std::make_shared<jt::MusicPlayer>());

    game->runGame(std::make_shared<StateMenu>(), gameloop);

    return 0;
}
