#include "Game.hpp"
#include "InputManager.hpp"
#include "KeyboardInput.hpp"
#include "MouseInput.hpp"
#include "Random.hpp"
#include "RenderWindow.hpp"
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

    auto const mouse = std::make_shared<jt::MouseInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    auto input = std::make_shared<jt::InputManager>(mouse, keyboard);

    game = std::make_shared<jt::Game>(
        std::make_shared<jt::RenderWindow>(800, 600, "Stresstest"), 2.0f, input, nullptr);
    game->setupRenderTarget();
    game->startGame(std::make_shared<StateSelect>(), gameloop);

    return 0;
}
