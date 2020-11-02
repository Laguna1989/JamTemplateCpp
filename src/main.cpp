#include "main.hpp"
#include "GameProperties.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/Random.hpp"
#include "StateMenu.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    hideConsoleInRelease();

    JamTemplate::Random::useTimeAsRandomSeed();

    JamTemplate::Game::Sptr game
        = std::make_shared<JamTemplate::Game>(800, 600, 2.0f, GP::GameName());
    auto window = game->getRenderWindow();

    game->switchState(std::make_shared<StateMenu>());

    sf::Clock clock;

    try {
        while (window->isOpen()) {
            sf::Time elapsed = clock.restart();
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
            }
            game->update(elapsed.asSeconds());
            game->draw();
        }
    } catch (std::exception const& e) {
        std::cerr << "!! ERROR: Exception ocurred !!\n";
        std::cerr << e.what() << std::endl;
        throw;
    } catch (...) {
        std::cerr << "!! ERROR: Unhandled Exception ocurred !!\n";
        std::terminate();
    }

    return 0;
}
