#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/Timer.hpp"
#include "../JamTemplate/Collision.hpp"
#include "../JamTemplate/ObjectGroup.hpp"
#include "../JamTemplate/SmartSprite.hpp"
#include "../JamTemplate/SmartShape.hpp"
#include "../JamTemplate/Tween.hpp"
#include "../JamTemplate/Game.hpp"

class State2 : public JamTemplate::GameState {
public:
	State2() = default;

private:
	JamTemplate::SmartShape::Sptr m_overlay;
	sf::RectangleShape m_sky;

	void doInternalUpdate(float const /*elapsed*/) override;

	void doCreate() override
	{

		m_sky = sf::RectangleShape(sf::Vector2f(200,150));
		m_sky.setFillColor(sf::Color{ 178, 255,255 });


		using JamTemplate::SmartShape;
		using JamTemplate::TweenAlpha;

		m_overlay = std::make_shared<SmartShape>();
		m_overlay->makeRect(sf::Vector2f{ 200,200 });
		m_overlay->setColor(sf::Color{ 0,0,0 });
		auto tw = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 255 }, sf::Uint8{ 0 });
		add(tw);
	}

	void drawSky() const
	{
		getGame()->getRenderTarget()->draw(m_sky);

	}

	void doDraw() const override
	{
		drawSky();
		drawObjects();
		m_overlay->draw(getGame()->getRenderTarget());
	}	
};

#endif
