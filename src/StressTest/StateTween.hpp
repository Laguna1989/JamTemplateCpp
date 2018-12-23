#ifndef STRESSTEST_STATE_TWEEN_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TWEEN_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/SmartShape.hpp"
#include "../JamTemplate/TweenAlpha.hpp"
#include "../JamTemplate/Game.hpp"

class StateTween : public JamTemplate::GameState {
public:
	StateTween() = default;

private:
	JamTemplate::SmartShape::Sptr m_overlayR;
	JamTemplate::SmartShape::Sptr m_overlayG;
	JamTemplate::SmartShape::Sptr m_overlayB;
	JamTemplate::SmartShape::Sptr m_background;

	void doInternalUpdate(float const /*elapsed*/) override;

	void doCreate() override
	{

		m_background = std::make_shared< JamTemplate::SmartShape>();
		m_background->makeRect(sf::Vector2f(200, 150));
		m_background->setColor(sf::Color{ 255, 255,255 });

		using JamTemplate::SmartShape;
		using JamTemplate::TweenAlpha;

		m_overlayR = std::make_shared<SmartShape>();
		m_overlayR->makeRect(sf::Vector2f{ 200,200 });
		m_overlayR->setColor(sf::Color{ 255,0,0,0});
		

		m_overlayG = std::make_shared<SmartShape>();
		m_overlayG->makeRect(sf::Vector2f{ 200,200 });
		m_overlayG->setColor(sf::Color{ 0,255,0,0 });
		
		m_overlayB = std::make_shared<SmartShape>();
		m_overlayB->makeRect(sf::Vector2f{ 200,200 });
		m_overlayB->setColor(sf::Color{ 0,0,255,0 });
		
		auto twRIn = TweenAlpha<SmartShape>::create(m_overlayR, 1.0f, sf::Uint8{ 0 }, sf::Uint8{ 125 });
		twRIn->addCompleteCallback([this]() {
			auto twROut = TweenAlpha<SmartShape>::create(m_overlayR, 1.0, sf::Uint8{ 125 }, sf::Uint8{ 0 });
			twROut->setStartDelay(1.5f);
			add(twROut);
		});
		add(twRIn);

		auto twGIn = TweenAlpha<SmartShape>::create(m_overlayG, 1.0f, sf::Uint8{ 0 }, sf::Uint8{ 125 });
		twGIn->setStartDelay(2.0f);
		twGIn->addCompleteCallback([this]() {
			auto twGOut = TweenAlpha<SmartShape>::create(m_overlayG, 1.0, sf::Uint8{ 125 }, sf::Uint8{ 0 });
			twGOut->setStartDelay(1.5f);
			add(twGOut);
		});
		add(twGIn);

		auto twBIn = TweenAlpha<SmartShape>::create(m_overlayB, 1.0f, sf::Uint8{ 0 }, sf::Uint8{ 125 });
		twBIn->setStartDelay(4.0f);
		twBIn->addCompleteCallback([this]() {
			auto twBOut = TweenAlpha<SmartShape>::create(m_overlayB, 1.0, sf::Uint8{ 125 }, sf::Uint8{ 0 });
			twBOut->setStartDelay(1.5f);
			add(twBOut);
		});
		add(twBIn);

		m_background->update(0);
		m_overlayR->update(0);
		m_overlayG->update(0);
		m_overlayB->update(0);
	}

	void doInternalDraw() const override
	{
		m_background->draw(getGame()->getRenderTarget());

		drawObjects();

		m_overlayR->draw(getGame()->getRenderTarget());
		m_overlayG->draw(getGame()->getRenderTarget());
		m_overlayB->draw(getGame()->getRenderTarget());
	}	
};

#endif
