#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#include <iostream>
#include "GameState.hpp"
#include "GameObject.hpp"

namespace JamTemplate
{

class Game final : public GameObject, public std::enable_shared_from_this<Game>{
public:
	using Sptr = std::shared_ptr<Game>;
	Game() : m_state{ nullptr }
	{
	}
	
	void switchState(GameState::Sptr newState)
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

	void setView(std::shared_ptr<sf::View> view)
	{
		m_view = view;
		if (m_renderTarget != nullptr)
			m_renderTarget->setView(*m_view);
	}
	std::shared_ptr<sf::View> getView()
	{
		return m_view;
	}

private:
	GameState::Sptr m_state{ nullptr };
	std::shared_ptr<sf::RenderTarget> m_renderTarget{nullptr};
	std::shared_ptr<sf::View> m_view{ nullptr };

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


}
#endif
