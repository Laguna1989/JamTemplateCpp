#include "StateGame.hpp"

#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenAlpha.hpp"
#include "JamTemplate/Game.hpp"
#include "GameProperties.hpp"
#include "Hud.hpp"
#include "TileMap.hpp"

void StateGame::doInternalUpdate (float const elapsed) 
{
	moveCamera(elapsed);
	m_overlay->update(elapsed);	
	m_tilemap->update(elapsed);
}

void StateGame::doInternalDraw() const 
{
	m_background->draw(getGame()->getRenderTarget());
	drawObjects();
	m_tilemap->draw();
	m_overlay->draw(getGame()->getRenderTarget());
	
}

void StateGame::doCreate()
{
	float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
	float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
	m_hud = std::make_shared<Hud>();
	
	using JamTemplate::TweenAlpha;
	using JamTemplate::SmartShape;

	m_background = std::make_shared < SmartShape>();
	m_background->makeRect({ w,h });
	m_background->setColor(GP::PaletteBackground());
	m_background->update(0.0f);

	m_overlay = std::make_shared<SmartShape>();
	m_overlay->makeRect(sf::Vector2f{ w,h });
	m_overlay->setColor(sf::Color{ 0,0,0 });
	m_overlay->update(0);
	auto tw = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 255 }, sf::Uint8{ 0 });
	tw->setSkipFrames();
	add(tw);


	doCreateInternal();
	add(m_hud);
}

void StateGame::doCreateInternal()
{
	
	m_tilemap = std::make_shared<Tilemap>();
	m_tilemap->setGameInstance(getGame()); 
	add(m_tilemap);
}


void StateGame::moveCamera(float elapsed)
{
	using im = JamTemplate::InputManager;
	using k = sf::Keyboard::Key;
	using vt = sf::Vector2f;
	using so = JamTemplate::SmartObject;
	if (im::pressed(k::A) || im::pressed(k::Left))
	{
		getGame()->getView()->move(vt{ -GP::Scrollspeed() * elapsed, 0 });
	}
	if (im::pressed(k::D) || im::pressed(k::Right))
	{
		getGame()->getView()->move(vt{ GP::Scrollspeed() * elapsed, 0 });
	}
	if (im::pressed(k::W) || im::pressed(k::Up))
	{
		getGame()->getView()->move(vt{ 0, -GP::Scrollspeed() * elapsed });
	}
	if (im::pressed(k::S) || im::pressed(k::Down))
	{
		getGame()->getView()->move(vt{ 0, GP::Scrollspeed() * elapsed });
	}
	//std::cout << so::getCamOffsetStatic().x << std::endl;
}