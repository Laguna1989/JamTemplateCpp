#include <SFML/Graphics.hpp>
#include "JamTemplate/Game.hpp"
#include "StateMenu.hpp"
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	JamTemplate::Game game(std::make_shared<StateMenu>());

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		game.update(elapsed.asSeconds());

		window.clear();
		game.draw();
		window.display();
	}

	return 0;
}
