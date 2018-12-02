#ifndef GAME_BALLOON_HPP_INCLUDEGUARD
#define GAME_BALLOON_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <random>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/Random.hpp"

class Balloon : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Balloon()
	{
		circ = sf::CircleShape(12);
		circ.setFillColor(sf::Color::Red);
		float x = JamTemplate::Random::getFloat(30, 200-24);
		setPosition({ x, 200 });
		//setVelocity({0, -GP::balloonMoveSpeed()});
		setAcceleration({ 0, -GP::balloonMoveSpeed() / 2 });
		setBoundsVelocity(sf::FloatRect(-GP::balloonMoveSpeed() , -GP::balloonMoveSpeed(), GP::balloonMoveSpeed()*2, GP::balloonMoveSpeed()*2));
	}

	~Balloon() = default;

	const sf::Shape& getShape() const { return circ; }
private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		circ.setPosition(getPosition());

		if (getPosition().y < -50)
		{
			kill();
		}
	}

	void doDraw() const override
	{
		getGame()->getRenderTarget()->draw(circ);
	}

	sf::CircleShape circ;
};

using BalloonPtr = std::shared_ptr<Balloon>;

#endif
