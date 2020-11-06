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
    game->switchState(std::make_shared<StateTileson>());
    auto window = game->getRenderWindow();
    window->setFramerateLimit(60);
    sf::Clock clock;

    sf::Font f = sf::Font {};
    f.loadFromFile("assets/font.ttf");
    sf::Text text { "", f };

    std::vector<float> times { 40, 0 };
    size_t idx = 0;

    std::ofstream out("fps.log");
    try {
        while (window->isOpen()) {
            sf::Time elapsed = clock.restart();
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
            }

            game->update(elapsed.asSeconds());

            times.at(idx) = 1.0f / elapsed.asSeconds();
            idx++;
            if (idx == times.size())
                idx = 0;

            float averageFPS = std::accumulate(times.begin(), times.end(), 0.0f) / times.size();
            out << averageFPS << "\n";

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
