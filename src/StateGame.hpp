#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Timer.hpp"
#include "JamTemplate/Collision.hpp"
#include "JamTemplate/ObjectGroup.hpp"
#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenAlpha.hpp"

#include "Player.hpp"
#include "Balloon.hpp"
#include "Shot.hpp"
#include "Hud.hpp"


class StateGame : public JamTemplate::GameState {
public:
	StateGame() = default;

	void spawnBalloon()
	{
		auto b = std::make_shared<Balloon>();
		add(b);
		m_balloons->push_back(b);
	}

	void spawnArrow(sf::Vector2f p)
	{
		auto s = std::make_shared<Shot>(p);
		add(s);
		m_shots->push_back(s);
	}

private:

	std::shared_ptr<Hud> m_hud;
	std::shared_ptr<Player> m_player;
	JamTemplate::ObjectGroup<Balloon>::Sptr m_balloons;
	JamTemplate::ObjectGroup<Shot>::Sptr m_shots;

	sf::RectangleShape m_sky;

	JamTemplate::SmartShape::Sptr m_overlay;

	void doInternalUpdate (float const elapsed) override
	{
		m_overlay->update(elapsed);
		for (auto const& sp : *m_shots)
		{
			auto s = sp.lock();
			for (auto const& bp : *m_balloons)
			{
				auto b = bp.lock();
				//if (JamTemplate::Collision::CircleTest<>(b->getShape(), s->getShape()))
				if (JamTemplate::Collision::BoundingBoxTest<>(b->getShape(), s->getShape()))
				{
					b->kill();
					m_hud->increaseScore();
				}
			}
		}
	}

	void doCreate() override
	{
		float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
		float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
		m_sky = sf::RectangleShape(sf::Vector2f(w,h));
		m_sky.setFillColor(sf::Color{ 178, 255,255});

		m_hud = std::make_shared<Hud>();
		add(m_hud);

		m_player = std::make_shared<Player>(*this);
		add(m_player);

		auto t = std::make_shared<JamTemplate::Timer>(GP::balloonSpawnTime(), [this]() {this->spawnBalloon(); }, -1);
		add(t);
		m_balloons = std::make_shared<JamTemplate::ObjectGroup<Balloon> >();
		add(m_balloons);
		m_shots = std::make_shared<JamTemplate::ObjectGroup<Shot> >();
		add(m_shots);
		
		using JamTemplate::TweenAlpha;
		using JamTemplate::SmartShape;

		m_overlay = std::make_shared<SmartShape>();
		m_overlay->makeRect(sf::Vector2f{ w,h });
		m_overlay->setColor(sf::Color{ 0,0,0 });
		m_overlay->update(0);
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
