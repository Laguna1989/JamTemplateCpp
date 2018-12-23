#include <fstream>

#include <SFML/Graphics.hpp>
#include "../JamTemplate/Game.hpp"

#include "State1.hpp"
#include "StateTween.hpp"

int main()
{
	JamTemplate::Game::Sptr game = std::make_shared<JamTemplate::Game>();
	game->setUp(800, 600, 4, "Stresstest");
	game->switchState(std::make_shared<StateTween>());
	auto window = game->getRenderWindow();
	sf::Clock clock;

	sf::Font f = sf::Font{};
	f.loadFromFile("assets/font.ttf");
	sf::Text text{"",f};
	
	std::vector<float> times{ 40,0 };
	size_t idx = 0;
	
	std::ofstream out("fps.log");

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

		times.at(idx) = 1.0f / elapsed.asSeconds();
		idx++;
		if (idx == times.size())
			idx = 0;

		float averageFPS = std::accumulate(times.begin(), times.end(), 0.0f)/ times.size();
		out << averageFPS << "\n";
		
		
		game->draw();
	}

	return 0;
}
