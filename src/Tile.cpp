#include "Tile.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/Game.hpp"
#include "GameProperties.hpp"


Tile::Tile(int tx, int ty) : m_tx{tx}, m_ty{ty}
{

}

void Tile::setBlocked(bool blocked)
{
	m_blocked = blocked;
}


void Tile::doUpdate(float const elapsed)
{
	m_spr->update(elapsed);
}

void Tile::doDraw() const
{
	m_spr->draw(getGame()->getRenderTarget());
}

void Tile::doCreate()
{
	m_spr = std::make_shared<JamTemplate::SmartSprite>();
	m_spr->setPosition(sf::Vector2f{ static_cast<float>(m_tx) * GP::TileSizeInPixel(),static_cast<float>(m_ty) * GP::TileSizeInPixel() });
	m_spr->setMoveWithCam(true);
}

void Tile::loadGraphic()
{
	if (m_tileType == TileType::GRASS)
	{
		setBlocked(false);
		int i = JamTemplate::Random::getInt(0, 5);
		if (i == 0)
			m_spr->loadSprite("assets/floor/grass/grass0.png");
		else if (i == 1)
			m_spr->loadSprite("assets/floor/grass/grass1.png");
		else if (i == 2)
			m_spr->loadSprite("assets/floor/grass/grass_flowers_red1.png");
		else if (i == 3)
			m_spr->loadSprite("assets/floor/grass/grass_flowers_blue1.png");
		else if (i == 4)
			m_spr->loadSprite("assets/floor/grass/grass_flowers_yellow1.png");
		else if (i == 5)
			m_spr->loadSprite("assets/floor/grass/grass1.png");
	}
	else if (m_tileType == TileType::WALL)
	{
		setBlocked(true);
		int i = JamTemplate::Random::getInt(0, 7);
		std::string fileName = "assets/wall/brick_brown" + std::to_string(i) + ".png";
		m_spr->loadSprite(fileName);
	}
	m_spr->update(0.01f);
}
