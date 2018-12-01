#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Timer.hpp"
#include "Player.hpp"
#include "Balloon.hpp"
#include "Shot.hpp"

class StateGame : public JamTemplate::GameState {
public:
	StateGame() = default;

	void spawnBalloon()
	{
		add(std::make_shared<Balloon>());
	}

	void spawnArrow(sf::Vector2f p)
	{
		auto s = std::make_shared<Shot>(p);
		add(s);
		m_shots.emplace_back(s);
	}

private:
	void doInternalUpdate (float const elapsed) override
	{
		
	}

	void doCreate() override
	{
		m_player = std::make_shared<Player>(*this);
		add(m_player);

		auto t = std::make_shared<JamTemplate::Timer>(GP::balloonSpawnTime(), [this]() {this->spawnBalloon(); }, -1);
		add(t);
	}

	std::shared_ptr<Player> m_player;
	std::vector<BalloonPtr> m_balloons;
	std::vector<std::weak_ptr<Shot>> m_shots;
};

#endif
