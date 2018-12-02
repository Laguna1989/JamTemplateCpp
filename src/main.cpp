#include <SFML/Graphics.hpp>
#include "JamTemplate/Game.hpp"
#include "StateMenu.hpp"

#include "JamTemplate/Noise.hpp"

int main()
{
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(200, 200), "SFML works!");
	JamTemplate::GamePtr game = std::make_shared<JamTemplate::Game>();
	game->switchState(std::make_shared<StateMenu>());
	game->setRenderTarget(window);
	window->setFramerateLimit(60);
	sf::Clock clock;

	

	while (window->isOpen())
	{
		sf::Time elapsed = clock.restart();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		
		game->update(elapsed.asSeconds());

		window->clear();
		game->draw();
		window->display();
	}

	return 0;
}
