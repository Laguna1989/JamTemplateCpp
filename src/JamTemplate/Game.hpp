#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#include <iostream>
#include "GameState.hpp"
#include "GameObject.hpp"
#include "Random.hpp"

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

	void Shake(float t, float strength, float shakeInterval = 0.005f)
	{
		m_shakeTimer = t;
		m_shakeStrength = strength;
		m_shakeInterval = m_shakeIntervalMax = shakeInterval;
	}

private:
	GameState::Sptr m_state{ nullptr };
	std::shared_ptr<sf::RenderTarget> m_renderTarget{nullptr};
	std::shared_ptr<sf::View> m_view{ nullptr };

	float m_shakeTimer{ -1.0f };
	float m_shakeStrength{ 0.0f };
	float m_shakeInterval{ 0.0f };
	float m_shakeIntervalMax{ 0.0f };
	sf::Vector2f m_shakeOffset{ 0,0 };

	std::weak_ptr<Game> getPtr() {
		return shared_from_this();
	}
	virtual void doUpdate(float const elapsed) override
	{
		if (m_state == nullptr)
			return;
		updateShake(elapsed);
		m_state->update(elapsed);
	};

	virtual void doDraw() const override
	{
		if (m_state == nullptr)
			return;
		m_state->draw();
	};

	void updateShake(float elapsed)
	{
		if (m_shakeOffset.x != 0 || m_shakeOffset.y != 0)
		{
			getView()->move(-m_shakeOffset.x, -m_shakeOffset.y);
		}

		if (m_shakeTimer > 0)
		{
			
			m_shakeTimer -= elapsed;
			m_shakeInterval -= elapsed;
			if (m_shakeInterval < 0)
			{
				m_shakeInterval = m_shakeIntervalMax;
				m_shakeOffset.x = JamTemplate::Random::getFloat(-m_shakeStrength, m_shakeStrength);
				m_shakeOffset.y = JamTemplate::Random::getFloat(-m_shakeStrength, m_shakeStrength);
			}
		}
		else
		{
			m_shakeOffset.x = m_shakeOffset.y = 0;
		}
		
		auto v = getView();
		v->move(m_shakeOffset.x, m_shakeOffset.y);
		setView(v);

	}

};


}
#endif
