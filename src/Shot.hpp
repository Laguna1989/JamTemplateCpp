#ifndef GAME_SHOT_HPP_INCLUDEGUARD
#define GAME_SHOT_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "JamTemplate/GameObject.hpp"
#include "JamTemplate/Transform.hpp"

class Shot : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Shot(sf::Vector2f p)
	{
		setPosition(p);
		setVelocity(sf::Vector2f{ 50,0 });
		std::cout << "Shot ctor" << std::endl;
		rect = sf::RectangleShape(sf::Vector2f(24, 4));
		rect.setFillColor(sf::Color::Blue);
	}

	~Shot()
	{
		std::cout << "Shot dtor" << std::endl;
	}

private:
	void doUpdate(float const elapsed) override
	{
		std::cout << "Shot update\n";
		updateTransform(elapsed);
		rect.setPosition(getPosition());
	}

	void doDraw() const override
	{
		getGame()->getRenderTarget()->draw(rect);
	}


	sf::RectangleShape rect;
};

using ShotPtr = std::shared_ptr<Shot>;

#endif