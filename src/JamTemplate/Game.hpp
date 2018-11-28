#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#include <iostream>
#include "GameState.hpp"
#include "GameObject.hpp"

namespace JamTemplate
{

class Game final : public GameObject, public std::enable_shared_from_this<Game>{
public:

	Game() : m_state{ nullptr }
	{
	}

	
	virtual void draw() const override 
	{
		if (m_state == nullptr)
			return;
		m_state->draw();
	};

	void switchState(GameStatePtr newState)
	{
		if (newState == nullptr)
			std::cerr << "cannot switch to nullptr state!" << std::endl;
		m_state = newState;
		m_state->setGameInstance(getptr());
	}

private:
	GameStatePtr m_state;
	std::weak_ptr<Game> getptr() {
		return shared_from_this();
	}
	virtual void doUpdate(float const elapsed) override
	{
		if (m_state == nullptr)
			return;
		m_state->update(elapsed);
	};
};

using GamePtr = std::shared_ptr<Game>;
}
#endif
