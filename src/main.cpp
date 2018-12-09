#include <SFML/Graphics.hpp>
#include "JamTemplate/Game.hpp"

#include "StateMenu.hpp"



int main()
{
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML works!");
	auto renderTexture = std::make_shared<sf::RenderTexture>();
	renderTexture->create(200, 150);
	renderTexture->setSmooth(false);

	auto view = std::make_shared<sf::View>(sf::FloatRect(0, 0, 200, 150));
	view->setViewport(sf::FloatRect(0, 0, 1, 1));
	JamTemplate::Game::Sptr game = std::make_shared<JamTemplate::Game>();
	game->switchState(std::make_shared<StateMenu>());
	game->setRenderTarget(renderTexture);
	game->setView(view);
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
		renderTexture->clear();
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
		window->display();
	}

	return 0;
}
