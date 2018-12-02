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
	
	void switchState(GameStatePtr newState)
	{
		if (newState == nullptr)
		{
			std::cerr << "cannot switch to nullptr state!" << std::endl;
			return;
		}
		m_state = newState;
		m_state->setGameInstance(getPtr());
		m_state->create();
	}

	void setRenderTarget(std::shared_ptr<sf::RenderTarget> rt)
	{
		m_renderTarget = rt;
	}
	std::shared_ptr<sf::RenderTarget> getRenderTarget()
	{
		return m_renderTarget;
	}

private:
	GameStatePtr m_state;
	std::shared_ptr<sf::RenderTarget> m_renderTarget{nullptr};

	std::weak_ptr<Game> getPtr() {
		return shared_from_this();
	}
	virtual void doUpdate(float const elapsed) override
	{
		if (m_state == nullptr)
			return;
		m_state->update(elapsed);
	};

	virtual void doDraw() const override
	{
		if (m_state == nullptr)
			return;
		m_state->draw();
	};

};

using GamePtr = std::shared_ptr<Game>;
}
#endif
