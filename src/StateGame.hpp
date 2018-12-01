#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Timer.hpp"
#include "JamTemplate/Collision.hpp"
#include "JamTemplate/ObjectGroup.hpp"

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
	void doInternalUpdate (float const elapsed) override
	{
		for (auto const& sp : *m_shots)
		{
			auto s = sp.lock();
			for (auto const& bp : *m_balloons)
			{
				auto b = bp.lock();
				if (JamTemplate::Collision::CircleTest<>(b->getShape(), s->getShape()))
				{
					b->kill();
					m_hud->increaseScore();
				}
			}
		}
	}

	void doCreate() override
	{
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
	}

	std::shared_ptr<Hud> m_hud;
	std::shared_ptr<Player> m_player;
	JamTemplate::ObjectGroupPtr<Balloon> m_balloons;
	JamTemplate::ObjectGroupPtr<Shot> m_shots;
};

#endif
