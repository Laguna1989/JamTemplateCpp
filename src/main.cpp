#include <SFML/Graphics.hpp>
#include "JamTemplate/Game.hpp"

#include "StateMenu.hpp"



int main()
{
	JamTemplate::Game::Sptr game = std::make_shared<JamTemplate::Game>();
	game->setUp(800, 600, 4, "SFML works!");

	auto window = game->getRenderWindow();
	auto renderTexture = game->getRenderTarget();
	auto view = game->getView();

	game->switchState(std::make_shared<StateMenu>());
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
		game->draw();
	}

	return 0;
}
