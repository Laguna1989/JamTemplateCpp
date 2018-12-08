#include <fstream>

#include <SFML/Graphics.hpp>
#include "../JamTemplate/Game.hpp"

#include "State1.hpp"
#include "State2.hpp"

int main()
{
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "JamTemplate Stresstest!");
	auto renderTexture = std::make_shared<sf::RenderTexture>();
	renderTexture->create(200, 150);
	renderTexture->setSmooth(false);

	auto view = std::make_shared<sf::View>(sf::FloatRect(0, 0, 200, 150));
	view->setViewport(sf::FloatRect(0, 0, 1, 1));
	JamTemplate::Game::Sptr game = std::make_shared<JamTemplate::Game>();
	game->switchState(std::make_shared<State2>());
	game->setRenderTarget(renderTexture);
	game->setView(view);
	//window->setFramerateLimit(60);
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
		
		
		
		window->clear();
		game->draw();
		// convert renderTexture to sprite and draw that. 
		const sf::Texture& texture = renderTexture->getTexture();
		sf::Sprite spr(texture);
		//Note: RenderTexture has a bug and is displayed upside down. 
		//This is corrected by the following two lines
		spr.setScale(sf::Vector2f(4, -4));
		spr.setPosition(0, 600);



		window->draw(spr);
		text.setString(std::to_string(averageFPS));
		window->draw(text);
		window->display();
	}

	return 0;
}
